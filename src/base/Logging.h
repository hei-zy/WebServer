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
        NUM_LOG_LEVELS  //��¼��־�ȼ�����
    };

    //��·����ȡ���ļ���
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

        const char *data_;  //�ļ���
        int size_;          //�ļ�������
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, LogLevel level);
    Logger(SourceFile file, int line, LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();
    
    Logger(Logger&& logger);    //ʹ�÷��������ͱ���ʵ�������������ƶ����죬�ƶ���ֵ
    Logger& operator=(Logger&& logger);
    
    LogStream& stream();

    static LogLevel logLevel();
    static void setLogLevel(LogLevel level);

    //ʹ��std::function������溯��ָ��
    using OutputFunc = std::function<void(const char*msg, int len)>;
    using FlushFunc = std::function<void()>;

    static void setOutput(OutputFunc);  //���� �����־ �ص�����
    static void setFlush(FlushFunc);    //���� ��ջ��� �ص�����

private:
    struct Impl;     //Pimpl----pointer to implementation
    std::unique_ptr<Impl> pImpl;    //RAII ʹ������ָ��
};

//ȫ�ֱ���---��־�ȼ�
extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
    return g_logLevel;
}


//�꺯��-----���ýӿ�,����Logger��ʱ������pImpl->stream��Ա����ʽ�������־
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