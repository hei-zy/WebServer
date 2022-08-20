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

    // ��������ڶ��߳��У�baseLoop_(mainLoop)��Ĭ������ѯ�ķ�ʽ����Channel��subLoop
    EventLoop *getNextLoop();

    std::vector<EventLoop *> getAllLoops(); //��������IO�̣߳����߳�ʱ����baseLoop_


    bool started() const { return started_; }
    const std::string name() const { return name_; }

private:
    EventLoop *baseLoop_; // ��acceptor����EventLoop��ͬ ����߳���Ϊ0 ��ֱ��ʹ��baseLoop_,���򴴽���EventLoop
    std::string name_;
    bool started_;
    int numThreads_;    //�߳���
    int next_; // ��ѯ���±�
    std::vector<std::unique_ptr<EventLoopThread>> threads_;    //IO�߳�����
    std::vector<EventLoop *> loops_;    //loopָ������
};