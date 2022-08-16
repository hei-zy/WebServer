#include "Thread.h"
#include "CurrentThread.h"

#include <assert.h>
#include<sys/prctl.h>

void CurrentThread::cacheTid()
{
    if (t_cachedTid == 0)
    {
        t_cachedTid = gettid();
        t_tidStringLength = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
    }
}

std::atomic_int Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string &name)
    : started_(false),
      joined_(false),
      tid_(0),
      func_(std::move(func)),
      name_(name),
      promise_()
{
    setDefaultName();
}

Thread::~Thread()
{
    if (started_ && !joined_)
    {
        thread_->detach();
    }
}

void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if (name_.empty())
    {
        char buf[32] = {0};
        snprintf(buf, sizeof(buf), "THread%d", num);
        name_ = buf;
    }
}

void Thread::start()
{
    assert(!started_);
    started_ = true;
    //�����߳�
    thread_ = std::make_unique<std::thread>([this]() {
        tid_=CurrentThread::tid();
        promise_.set_value(); //֪ͨ�߳�������ɣ�һ��֪ͨ

        CurrentThread::t_threadName = name_.empty() ? "Thread" : name_.c_str();
        prctl(PR_SET_NAME, CurrentThread::t_threadName);
        
        func_();

        CurrentThread::t_threadName = "finished"; });
        
    promise_.get_future().wait(); //�ȴ��߳��������,����߳�����ʧ�ܣ��ͻ�����
    assert(tid_ > 0);
}

void Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    thread_->join();
}