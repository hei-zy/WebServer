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

    //向缓冲区中写入数据
    void append(const char* logline, int len);

    //启动线程
    void start();

    //停止线程
    void stop();

private:
    //异步线程函数，通过LogFile定时将 缓冲区的数据 写入 文件 中
    void threadFunc();

    using Buffer = FixedBuffer<kLargeBuffer>;
    using BufferPtr = std::unique_ptr<Buffer>;
    using BufferVector = std::vector<BufferPtr>;

    const std::string basename_;
    const off_t rollSize_;
    const int flushInterval_;

    std::atomic<bool> running_; //线程运行标志位
    Thread thread_;
    std::promise<void> promise_; //一次性通信使用promise<void>
    std::mutex mutex_;
    std::condition_variable cond_;

    BufferPtr currentBuffer_; //双缓冲机制
    BufferPtr nextBuffer_;
    BufferVector buffers_; //存放缓冲区的vector，双缓冲不够时，创建新的缓冲
};