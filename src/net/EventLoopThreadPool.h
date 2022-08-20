#pragma once

#include "src/base/noncopyable.h"

#include <functional>
#include <memory>
#include <vector>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool:noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;

    EventLoopThreadPool(EventLoop *baseLoop, const std::string &nameArg);
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads) { numThreads_ = numThreads; }
    
    void start(const ThreadInitCallback &cb = ThreadInitCallback());

    // 如果工作在多线程中，baseLoop_(mainLoop)会默认以轮询的方式分配Channel给subLoop
    EventLoop *getNextLoop();

    std::vector<EventLoop *> getAllLoops(); //返回所有IO线程，单线程时返回baseLoop_


    bool started() const { return started_; }
    const std::string name() const { return name_; }

private:
    EventLoop *baseLoop_; // 与acceptor所属EventLoop相同 如果线程数为0 那直接使用baseLoop_,否则创建多EventLoop
    std::string name_;
    bool started_;
    int numThreads_;    //线程数
    int next_; // 轮询的下标
    std::vector<std::unique_ptr<EventLoopThread>> threads_;    //IO线程数组
    std::vector<EventLoop *> loops_;    //loop指针数组
};