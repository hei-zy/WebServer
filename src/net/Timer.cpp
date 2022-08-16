#include"Timer.h"

std::atomic_int Timer::s_numCreated_;

void Timer::restart(Timestamp now)
{
    if(repeat_)
    {
        expiration_=addTime(now,interval_); //����interval�õ��µ�Timestamp
    }
    else
    {
        expiration_=Timestamp();    //���
    }
}