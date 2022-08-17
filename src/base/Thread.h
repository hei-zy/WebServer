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
    pid_t tid_;                           //�߳�pid�������߳�ʱ��
    ThreadFunc func_;                     //�̻߳ص�����
    std::string name_;                    //�߳�������û���룬Ĭ�ϰ��������
    std::unique_ptr<std::thread> thread_; //�̣߳�RAII
    std::promise<void> promise_;          //����ͨ��ʹ��promise<void>������ʹ���������������Ļ�����������
    static std::atomic_int numCreated_;   //�����߳���
};