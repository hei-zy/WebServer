#pragma once
#include<stdio.h>
#include<string.h>
#include<string>
#include<functional>
#include<memory>

#include"LogStream.h"

class Logger
{
public:
    enum LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS  //记录日志等级数量
    };

    //从路径中取出文件名
    struct SourceFile
    {
        //char[N]
        template<int N>
        SourceFile(const char (&arr)[N])
            :data_(arr),
            size_(N-1)
        {
            const char*slash=strrchr(data_,'/');
            if(slash) 
            {
                data_=slash+1;
                size_-=static_cast<int>(data_-arr);
            }
        }
        //char*
        explicit SourceFile(const char *filename)
            : data_(filename)
        {
            const char *slash = strrchr(filename, '/');
            if (slash)
            {
                data_ = slash + 1;
            }
            size_ = static_cast<int>(strlen(data_));
        }

        const char *data_;  //文件名
        int size_;          //文件名长度
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, LogLevel level);
    Logger(SourceFile file, int line, LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();
    
    Logger(Logger&& logger);    //使用非完整类型必须实现析构函数，移动构造，移动赋值
    Logger& operator=(Logger&& logger);
    
    LogStream& stream();

    static LogLevel logLevel();
    static void setLogLevel(LogLevel level);

    //使用std::function对象代替函数指针
    using OutputFunc = std::function<void(const char*msg, int len)>;
    using FlushFunc = std::function<void()>;

    static void setOutput(OutputFunc);  //设置 输出日志 回调函数
    static void setFlush(FlushFunc);    //设置 清空缓存 回调函数

private:
    struct Impl;     //Pimpl----pointer to implementation
    std::unique_ptr<Impl> pImpl;    //RAII 使用智能指针
};

//全局变量---日志等级
extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
    return g_logLevel;
}


//宏函数-----调用接口,返回Logger临时对象中pImpl->stream成员，格式化输出日志
#define LOG_TRACE\
    if(Logger::logLevel()<=Logger::TRACE)\
    Logger(__FILE__,__LINE__,Logger::TRACE,__func__).stream()
#define LOG_DEBUG\
    if(Logger::logLevel()<=Logger::DEBUG)\
    Logger(__FILE__,__LINE__,Logger::DEBUG,__func__).stream()
#define LOG_INFO\
    if(Logger::logLevel()<=Logger::INFO)\
    Logger(__FILE__,__LINE__).stream()
#define LOG_WARN Logger(__FILE__,__LINE__,Logger::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).stream()
#define LOG_SYSERR Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL Logger(__FILE__, __LINE__, true).stream()