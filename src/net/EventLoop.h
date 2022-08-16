#pragma once

#include "src/base/CurrentThread.h"
#include "src/base/Timestamp.h"
#include "src/base/noncopyable.h"
#include "TimerId.h"

#include <vector>
#include <atomic>
#include <mutex>
#include <memory>
#include <functional>

class Channel;
class Poller;
class TimerQueue;

class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;
    using TimerCallback = std::function<void()>;

    EventLoop();
    ~EventLoop();

    // 开启事件循环
    void loop();
    // 退出事件循环(quit_=true)
    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    // 可跨线程调用,在当前loop（IO线程）中直接执行cb，否则调用queueInLoop()
    void runInLoop(Functor cb);
    // 把上层注册的回调函数cb放入队列中 唤醒loop所在的线程执行cb
    void queueInLoop(Functor cb);

    size_t queueSize() const; //返回pendingFunctors_中回调函数的数量

    // timers------------------------------------------------------
    //  使用定时器
    TimerId runAt(Timestamp time, TimerCallback cb);

    //使用定时器---在一定时间后
    TimerId runAfter(double delay, TimerCallback cb);

    // 使用定时器---可重复
    TimerId runEvery(double interval, TimerCallback cb);

    ///通过timerId取消定时器
    void cancel(TimerId timerId);

    // 通过向wakeupFd_(eventfd)中写一个数据，唤醒loop所在的线程
    void wakeup();

    // EventLoop的方法 => Poller的方法
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    // 判断EventLoop对象是否在自己的线程里
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); } // threadId_为EventLoop创建时的线程id CurrentThread::tid()为当前线程id

    static EventLoop *getEventLoopOfCurrentThread();

private:
    void abortNotInLoopThread();
    void handleRead();        // 给eventfd返回的文件描述符wakeupFd_绑定的事件回调 当wakeup()时 即有事件发生时 调用handleRead()读wakeupFd_的8字节 同时唤醒阻塞的epoll_wait
    void doPendingFunctors(); // 执行上层回调，通过swap()将pendingFunctors_换到局部变量中
                              // 1、减小临界区长度；2、可以不用阻塞其他线程调用queueInLoop()；

    using ChannelList = std::vector<Channel *>;

    std::atomic_bool looping_;                //是否在loop()
    std::atomic_bool quit_;                   // 标识退出loop循环
    std::atomic_bool eventHandling_;          //  是否在处理事件
    std::atomic_bool callingPendingFunctors_; //是否在处理pendingFunctors_

    const pid_t threadId_; // 记录当前EventLoop是被哪个线程id创建的 即标识了当前EventLoop的所属线程id

    Timestamp pollReturnTime_; // Poller返回发生事件的Channels的时间点

    std::unique_ptr<Poller> poller_;
    std::unique_ptr<TimerQueue> timerQueue_; //定时器，调用addtimer(),cancel()

    int wakeupFd_; // 当mainLoop获取一个新用户的Channel 需通过轮询算法选择一个subLoop 通过该成员唤醒subLoop处理Channel
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_; // 返回Poller检测到当前有事件发生的所有Channel列表
    Channel *currentActiveChannel_;

    mutable std::mutex mutex_;             // 互斥锁 用来保护pendingFunctors_的线程安全操作
    std::vector<Functor> pendingFunctors_; // 存储loop需要执行的所有回调操作，任务队列
};