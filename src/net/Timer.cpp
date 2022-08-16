#include"Timer.h"

std::atomic_int Timer::s_numCreated_;

void Timer::restart(Timestamp now)
{
    if(repeat_)
    {
        expiration_=addTime(now,interval_); //加上interval得到新的Timestamp
    }
    else
    {
        expiration_=Timestamp();    //清空
    }
}