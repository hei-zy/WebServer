#include"CurrentThread.h"

namespace CurrentThread
{
    // 缓存线程pid等信息，避免多次调用 系统调用 耗时
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread int t_tidStringLength = 6;
    __thread const char *t_threadName = "unknown";
}