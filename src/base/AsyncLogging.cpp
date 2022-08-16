#include "AsyncLogging.h"
#include "LogFile.h"
#include "Timestamp.h"

#include <assert.h>

AsyncLogging::AsyncLogging(const std::string &basename,
                           off_t rollSize,
                           int flushInterval)
    : basename_(basename),
      rollSize_(rollSize),
      flushInterval_(flushInterval),
      running_(false),
      thread_([this]()
              { this->threadFunc(); },
              "Logging"),
      promise_(),
      mutex_(),
      cond_(),
      currentBuffer_(std::make_unique<Buffer>()),
      nextBuffer_(std::make_unique<Buffer>()),
      buffers_()
{
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);
}

AsyncLogging ::~AsyncLogging()
{
    if (running_)
    {
        stop();
    }
}

void AsyncLogging::append(const char *logline, int len)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (currentBuffer_->avail() > len)
    {
        currentBuffer_->append(logline, len);
    }
    else
    {
        buffers_.emplace_back(std::move(currentBuffer_));
        if (nextBuffer_)
        {
            currentBuffer_ = std::move(nextBuffer_);
        }
        else
        {
            currentBuffer_.reset(new Buffer);
        }
        currentBuffer_->append(logline, len);
        cond_.notify_one();
    }
}

void AsyncLogging::start()
{
    running_ = true;
    thread_.start();
    promise_.get_future().wait();
}

void AsyncLogging::stop()
{
    running_ = false;
    cond_.notify_one();
    thread_.join();
}

void AsyncLogging::threadFunc()
{
    assert(running_ == true);
    promise_.set_value();
    LogFile output(basename_, rollSize_, false);
    auto newBuffer1(std::make_unique<Buffer>());
    auto newBuffer2(std::make_unique<Buffer>());
    newBuffer1->bzero();
    newBuffer2->bzero();
    BufferVector buffersToWrite;
    buffersToWrite.reserve(16);
    while (running_)
    {
        assert(newBuffer1 && newBuffer1->length() == 0);
        assert(newBuffer2 && newBuffer2->length() == 0);
        assert(buffersToWrite.empty());

        {
            std::unique_lock<std::mutex> lock(mutex_);
            if (buffers_.empty())
            {
                cond_.wait_for(lock, std::chrono::seconds(flushInterval_));
            }
            buffers_.emplace_back(std::move(currentBuffer_));
            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_);
            if (!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
        }
        assert(!buffersToWrite.empty());
        //如果缓存区大于25，只保留前两个缓存区，删除多余缓存区
        if (buffersToWrite.size() > 25)
        {
            char buf[256];
            snprintf(buf, sizeof buf, "Dropped log messages at %s, %zd larger buffers\n",
                     Timestamp::now().toString().c_str(),
                     buffersToWrite.size() - 2);
            fputs(buf, stderr);
            output.append(buf, static_cast<int>(strlen(buf)));
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }

        for (const auto &buffer : buffersToWrite)
        {
            //通过LogFile输出 缓冲数据 到 文件
            output.append(buffer->data(), buffer->length());
        }

        //留下两个缓存区清空后 下次使用，避免重复申请缓存区
        if (buffersToWrite.size() > 2)
        {
            buffersToWrite.resize(2);
        }
        if (!newBuffer1)
        {
            assert(!buffersToWrite.empty());
            newBuffer1 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }
        if (!newBuffer2)
        {
            assert(!buffersToWrite.empty());
            newBuffer2 = std::move(buffersToWrite.back());
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }
        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}