#pragma once

#include<string>
#include"noncopyable.h"

class AppendFile : noncopyable
{
public:
    explicit AppendFile(std::string filename);
    ~AppendFile();
    // append����־��д
    void append(const char *logline, const size_t len);
    void flush(); //��ջ�����
    off_t writtenBytes() const {return writtenBytes_;}
private:
    size_t write(const char *logline, size_t len);

private:
    FILE *fp_;
    char buffer_[64 * 1024];
    off_t writtenBytes_;
};