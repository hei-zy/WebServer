# High Performance WebServer
------------
* linux系统下使用C++实现的[高并发服务器](https://github.com/hei-zy/WebServer/tree/main/src/server)，并实现了[双缓冲异步日志](https://github.com/hei-zy/WebServer/tree/master/src/base)，记录服务器运行状态。
* 参考muduo网络库与《Linux高性能服务器编程》
## Technical points
* 利用IO复用技术Epoll与线程池实现多线程的Reactor高并发模型（one loop per thread）；
* 使用eventfd实现了线程的异步唤醒；
* 采用时间堆的方式与惰性删除的方式处理定时器超时事件；
* 使用timerfd实现定时器与epoll之间更好的融合，可以使用统一的方式处理超时事件，IO事件；
* 利用标准库容器vector封装char，实现自动增长的缓冲区；
* 使用双缓冲区技术实现异步日志系统,记录服务器运行状态；
* 为减少内存泄漏的可能，使用智能指针等RAII机制；
* 使用lambda表达式代替std::bind增加代码可读性；
  
## 环境要求
* Linux
* C++17
## 快速运行
```bash
sh ./build.sh
./build/bin/server [-p port] [-t thread_numbers]
```
```
* 默认端口号:9527
* 默认线程数:1
```

# 并发模型
*  Reactors+thread pool(one loop per thread),为避免线程频繁创建和销毁带来的开销，使用线程池，在程序的开始创建固定数量的线程。使用epoll作为IO多路复用的实现方式。
*  主线程(accptor所在线程)负责接收新连接，并通过轮询的方式将新连接分发给子线程(subLoop)，通过runInLoop()保证线程安全，向subloop中注册读事件

# 定时器
* 每个SubReactor持有一个定时器，用于处理超时请求和长时间不活跃的连接。
* 采用时间堆的方式，删除定时器时采用惰性删除（将其标志位设为true），降低删除定时器的时间复杂度。即时间的到来不会唤醒线程，而是每次循环的最后进行检查，如果超时了再删，因为这里对超时的要求并不会很高，如果此时线程忙，那么检查时间队列的间隔也会短，如果不忙，也给了超时请求更长的等待时间。
* `timedfd_created` 把时间变成一个文件描述符，在定时器超时的那一刻变得可读，可很好的与select/poll框架结合，用统一的方式来处理IO事件与超时事件。

#  线程间通信
>* 创建线程之后主线程和子线程谁先运行是不确定的。通过一个`eventfd`在线程之间传递数据的好处是多个线程无需上锁就可以实现同步。创建`wakeupfd` 用来notify唤醒subReactor处理新来的channel


执行当前EventLoop事件循环需要处理的回调操作 对于线程数 >=2 的情况 IO线程 mainloop(mainReactor) 主要工作：
* `accept`接收连接 => 将accept返回的connfd打包为Channel => `TcpServer::newConnection` 通过轮询将`TcpConnection`对象分配给subloop处理
* mainloop调用`queueInLoop`将回调加入subloop（该回调需要subloop执行 但subloop还在poller_->poll处阻塞） `queueInLoop`通过`wakeup`将subloop唤醒

# 核心结构
* `Channel`类：Channel是Reactor结构中的“事件”，它自始至终都属于一个EventLoop，负责一个文件描述符的IO事件，在Channel类中保存这IO事件的类型以及对应的回调函数，当IO事件发生时，最终会调用到Channel类中的回调函数。因此，程序中所有带有读写时间的对象都会和一个Channel关联，包括loop中的eventfd，listenfd，timerfd等。
* `EventLoop`类：One loop per thread意味着每个线程只能有一个EventLoop对象，EventLoop即是时间循环，每次从poller里拿活跃事件，并给到Channel里分发处理。EventLoop中的loop函数会在最底层(Thread)中被真正调用，开始无限的循环，直到某一轮的检查到退出状态后从底层一层一层的退出。
## EventLoop功能
* __one loop per thread__ 意思是每个线程最多只有一个EventLoop对象
* __`EventLoop`__ 对象构造时，会检查当前线程是否已经创建了其他EventLoop对象，如果已创建，终止程序（**LOG_FATAL**）
* __`EventLoop`__ 构造函数会记住本对象所属线程（**threadId_**）
* 创建了 __`EventLoop`__ 对象的线程为 __IO线程__，功能是运行事件循环（**`EventLoop::loop`**）

## EventLoopThread功能
* __`EventLoopThread`__ 创建了一个线程，在线程函数创建一个`EventLoop`对象并调用`EventLoop::loop` 

## Channel使用EventLoop的裸指针(raw pointer)记录其所属loop  
* 因为`Channel`只属于一个loop，且loop失效时，channel也应该失效，所以在loop析构函数中，释放其拥有的channel。故Channel中使用EventLoop的裸指针不会带来内存泄露的问题。    

## Poller中Channel对象索引
* 采用`unordered_map<int,Channel*>`数据结构作为Channel索引，文件描述符作为key值，提高查找效率。

## 使用LT模式的原因
* 增加与poll，select之间的兼容性，文件描述符较少时，epoll效率不一定高。
* 读写时不必等待EAGAIN，减少系统调用次数，降低延迟。

# Log设计
Log的实现分为前端和后端，前端往后端写，后端往磁盘写。Log前端是前面所述的IO线程，负责产生log，后端是Log线程，设计了多个缓冲区，负责收集前端产生的log，集中往磁盘写
后端主要是由多个缓冲区构成的，集满了或者时间到了就向文件写一次。日志系统主要由以下五个类组成：
* __FileUtil__ 最底层的文件类AppendFile，封装了Log文件的打开、写入并在类析构的时候关闭文件，底层使用了标准IO，该append函数直接向文件写。
* __LogFile__ 封装AppendFile，加锁实现线程安全，并满足一定条件时（时间，次数，缓冲区写满等）刷新缓存区，并更换文件。
* __AsyncLogging__ 负责启动一个log线程，专门用来将log写入LogFile，应用了“双缓冲技术”，双缓冲区不够时，自动创建多个缓冲区。但当数据过多，缓冲区数量过多，只保留前两个缓冲区，删除多余缓冲区中的数据。AsyncLogging负责(定时到或被填满时)将缓冲区中的数据写入LogFile中。
* __LogStream__ 主要用来格式化输出，重载了<<运算符，同时也有自己的一块缓冲区，这里缓冲区的存在是为了缓存一行，把多个<<的结果连成一块。并且可通过设置回调函数，自定义日志输出函数（指定日志日志输出方式，文件）。
* __Logging__ 对外接口，通过宏函数创建logger临时对象，logger对象中内涵logStream对象，实现格式化打印日志信息。

# [压力测试](./test_presure)
* OS: Ubuntu 20.04 单核 4G
* Complier: g++ 9.4.0
* 服务器5线程，8000client并发下正常运行
