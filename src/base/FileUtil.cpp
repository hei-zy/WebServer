#include"FileUtil.h"
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<assert.h>
#include<sys/stat.h>

AppendFile::AppendFile(std::string filename)
    : fp_(::fopen(filename.c_str(), "ae")), // 'e' for O_CLOEXEC(调用exec系列函数文件指针不会被继承)
      writtenBytes_(0)
{
    assert(fp_);
    ::setbuffer(fp_, buffer_, sizeof(buffer_));
}

AppendFile::~AppendFile()
{
    ::fclose(fp_);
}

void AppendFile::append(const char* logline, const size_t len) 
{
    size_t written=0;
    while(written!=len)
    {
        size_t remain=len-written;
        size_t n=write(logline+written, remain);
        if(n!=remain)
        {
            int err=ferror(fp_);
            if(err)
            {
                fprintf(stderr,"AppendFile::append() failed %d\n", error_t(err));
                break;
            }
        }
        written+=n;
    }
    writtenBytes_+=written;
}

void AppendFile::flush()
{
    ::fflush(fp_);
}

size_t AppendFile::write(const char* logfile, size_t len)
{
    //不加锁读文件，线程不安全，但更快
    return ::fwrite_unlocked(logfile, 1, len, fp_);
}