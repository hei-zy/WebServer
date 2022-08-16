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

//��������loop������Ϊloop����ջ���󣬻��Զ��ͷ�
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
        loops_.emplace_back(t->startLoop()); // �ײ㴴���߳� ��һ���µ�EventLoop �����ظ�loop�ĵ�ַ
    }
    if (numThreads_ == 0 && cb) // ���������ֻ��һ���߳�����baseLoop
    {
        cb(baseLoop_);
    }
}

// ��������ڶ��߳��У�baseLoop_(mainLoop)��Ĭ������ѯ�ķ�ʽ����Channel��subLoop
EventLoop *EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop *loop = baseLoop_; // ���ֻ����һ���߳� Ҳ����ֻ��һ��mainReactor ��subReactor ��ô��ѯֻ��һ���߳� getNextLoop()ÿ�ζ����ص�ǰ��baseLoop_
    if (!loops_.empty())         // ͨ����ѯ��ȡ��һ�������¼���loop
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
