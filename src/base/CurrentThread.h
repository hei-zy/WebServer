#include<stdint.h>
#include<unistd.h>

#include <cxxabi.h>
#include <execinfo.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include"stdio.h"

namespace CurrentThread
{
    // 缓存线程pid等信息，避免多次调用 系统调用 耗时
    extern __thread int t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char *t_threadName;
    void cacheTid();

    inline pid_t gettid()
    {
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }


    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }

    inline const char *tidString() // for logging
    {
        return t_tidString;
    }

    inline int tidStringLength() // for logging
    {
        return t_tidStringLength;
    }

    inline const char *name() { return t_threadName; }
}