#pragma once

#include <vector>
#include <string>
#include <memory>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>

#include "LogStream.h"
#include "noncopyable.h"
#include "Thread.h"

class AsyncLogging : noncopyable
{
public:
    AsyncLogging(const std::string &basename,
                 off_t rollSize,
                 int flushInterval = 3);

    ~AsyncLogging();

    //�򻺳�����д������
    void append(const char* logline, int len);

    //�����߳�
    void start();

    //ֹͣ�߳�
    void stop();

private:
    //�첽�̺߳�����ͨ��LogFile��ʱ�� ������������ д�� �ļ� ��
    void threadFunc();

    using Buffer = FixedBuffer<kLargeBuffer>;
    using BufferPtr = std::unique_ptr<Buffer>;
    using BufferVector = std::vector<BufferPtr>;

    const std::string basename_;
    const off_t rollSize_;
    const int flushInterval_;

    std::atomic<bool> running_; //�߳����б�־λ
    Thread thread_;
    std::promise<void> promise_; //һ����ͨ��ʹ��promise<void>
    std::mutex mutex_;
    std::condition_variable cond_;

    BufferPtr currentBuffer_; //˫�������
    BufferPtr nextBuffer_;
    BufferVector buffers_; //��Ż�������vector��˫���岻��ʱ�������µĻ���
};