#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include<future>
#include <sys/types.h>

#include "noncopyable.h"

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc, const std::string &name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() { return started_; }
    pid_t tid() const { return tid_; }
    const std::string &name() const { return name_; }

    static int numCreated() { return numCreated_; }

private:
    void setDefaultName();

    bool started_;
    bool joined_;
    pid_t tid_;                           //线程pid，创建线程时绑定
    ThreadFunc func_;                     //线程回调函数
    std::string name_;                    //线程名，若没输入，默认按编号命名
    std::unique_ptr<std::thread> thread_; //线程，RAII
    std::promise<void> promise_;          //单次通信使用promise<void>，减少使用条件变量带来的互斥量的消耗
    static std::atomic_int numCreated_;   //创建线程数
};