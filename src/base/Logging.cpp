#include "Logging.h"
#include "Timestamp.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sstream>

char t_errnobuf[512]; //储存错误描述的缓存
const char *strerror_tl(int savedErrno)
{
    return strerror_r(savedErrno, t_errnobuf, sizeof t_errnobuf);
}

const char *LogLevelName[Logger::NUM_LOG_LEVELS] =
{
        "TRACE ",
        "DEBUG ",
        "INFO  ",
        "WARN  ",
        "ERROR ",
        "FATAL ",
};

void defaultOutput(const char *msg, int len)
{
    size_t n = fwrite(msg, 1, len, stdout);
    // FIXME check n
    (void)n;
}

void defaultFlush()
{
    fflush(stdout);
}

Logger::OutputFunc g_output=defaultOutput; // output回调函数对象
Logger::FlushFunc g_flush=defaultFlush;   // flush回调函数对象

// Impl实现
struct Logger::Impl
{
    using LogLevel = Logger::LogLevel;
    Impl(LogLevel level, int savedErrno, const SourceFile &file, int line)
        : level_(level),
          basename_(file),
          line_(line),
          time_(Timestamp::now()),
          stream_()
    {
        formatTime();
        stream_ << LogLevelName[level];
        if (savedErrno != 0)
        {
            stream_ << strerror_tl(savedErrno) << " (errno=" << savedErrno << ") ";
        }
    }

    void formatTime()
    {
        stream_ << Timestamp::now().toString();
    }

    void finish()
    {
        stream_ << "-" << basename_.data_ << ":" << line_ << '\n';
    }

    LogLevel level_;
    SourceFile basename_;
    int line_;
    Timestamp time_;
    LogStream stream_;
};

Logger::Logger(SourceFile file, int line)
    : pImpl(new Impl(INFO, 0, file, line)) {}

Logger::Logger(SourceFile file, int line, LogLevel level)
    : pImpl(new Impl(level, 0, file, line)) {}

Logger::Logger(SourceFile file, int line, LogLevel level, const char *func)
    : pImpl(new Impl(level, 0, file, line))
{
    pImpl->stream_ << func << ' ';
}

Logger::Logger(SourceFile file, int line, bool toAbort)
    : pImpl(new Impl(toAbort ? FATAL : ERROR, errno, file, line)) {}

Logger::Logger(Logger &&logger) = default;

Logger &Logger::operator=(Logger &&logger) = default;




Logger::~Logger()
{
    pImpl->finish();
    //将 缓存区pImpl->stream_.buffer 中的数据 通过g_output回调写入文件
    const LogStream::Buffer &buf(this->stream().buffer());
    g_output(buf.data(), buf.length());
    if (pImpl->level_ == FATAL)
    {
        g_flush();
        abort();
    }
}

LogStream &Logger::stream()
{
    return pImpl->stream_;
}

//初始化日志等级
Logger::LogLevel g_logLevel = Logger::INFO;

void Logger::setLogLevel(LogLevel level)
{
    g_logLevel=level;
}

void Logger::setOutput(OutputFunc out)
{
    g_output=out;
}

void Logger::setFlush(FlushFunc flush)
{
    g_flush=flush;
}