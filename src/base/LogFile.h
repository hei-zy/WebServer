#pragma once

//封装AppendFile，加锁实现线程安全，并满足一定条件时刷新缓存区
#include <memory>
#include <mutex>
#include <string>

#include "noncopyable.h"

class AppendFile;

using std::string;
class LogFile : noncopyable
{
public:
    LogFile(const string &basename,
            off_t rollSize,
            bool threadSafe = true,
            int flushInterval = 3,
            int checkEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile(); //更换文件
private:
    void append_unlocked(const char* logline, int len);

    static string getLogFileName(const string& basename, time_t* now);
private:
    const string basename_;     //文件名前缀
    const off_t rollSize_;      //缓冲区大小
    const int flushInterval_;   //刷新缓冲区的时间间隔
    const int checkEveryN_;     //调用write次数上限

    int count_; //调用write次数

    std::unique_ptr<std::mutex> uniMutex_;
    time_t startOfPeriod_;
    time_t lastRoll_;
    time_t lastFlush_;
    std::unique_ptr<AppendFile> file_;

    const static int kRollPerSeconds_=60*60*24;
};