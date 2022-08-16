#include <memory>
#include <stdio.h>
#include <assert.h>

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg)
    : baseLoop_(baseLoop),
      name_(nameArg),
      started_(false),
      numThreads_(0),
      next_(0),
      threads_(),
      loops_() {}

//不用销毁loop对象，因为loop都是栈对象，会自动释放
EventLoopThreadPool::~EventLoopThreadPool() = default;

void EventLoopThreadPool::start(const ThreadInitCallback &cb)
{
    assert(!started_);
    baseLoop_->assertInLoopThread();
    started_ = true;

    for (int i = 0; i < numThreads_; ++i)
    {
        char buf[name_.size() + 32];
        snprintf(buf, sizeof(buf), "%s%d", name_.c_str(), i);
        // EventLoopThread *t = new EventLoopThread(cb, buf);
        auto t = std::make_unique<EventLoopThread>(cb, std::string(buf));
        threads_.emplace_back(std::move(t));
        loops_.emplace_back(t->startLoop()); // 底层创建线程 绑定一个新的EventLoop 并返回该loop的地址
    }
    if (numThreads_ == 0 && cb) // 整个服务端只有一个线程运行baseLoop
    {
        cb(baseLoop_);
    }
}

// 如果工作在多线程中，baseLoop_(mainLoop)会默认以轮询的方式分配Channel给subLoop
EventLoop *EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop *loop = baseLoop_; // 如果只设置一个线程 也就是只有一个mainReactor 无subReactor 那么轮询只有一个线程 getNextLoop()每次都返回当前的baseLoop_
    if (!loops_.empty())         // 通过轮询获取下一个处理事件的loop
    {
        loop = loops_[next_++];
        if (static_cast<size_t>(next_) >= loops_.size())
        {
            next_ = 0;
        }
    }
    return loop;
}

std::vector<EventLoop *> EventLoopThreadPool::getAllLoops()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    if (loops_.empty())
    {
        return {baseLoop_};
    }
    else
    {
        return loops_;
    }
}
