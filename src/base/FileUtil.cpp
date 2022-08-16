#include"FileUtil.h"
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<assert.h>
#include<sys/stat.h>

AppendFile::AppendFile(std::string filename)
    : fp_(::fopen(filename.c_str(), "ae")), // 'e' for O_CLOEXEC(����execϵ�к����ļ�ָ�벻�ᱻ�̳�)
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
    //���������ļ����̲߳���ȫ��������
    return ::fwrite_unlocked(logfile, 1, len, fp_);
}