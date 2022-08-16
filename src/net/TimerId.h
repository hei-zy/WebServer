#pragma once

class Timer;

//对外接口，删除定时器时通过cancel()通过TimerId删除
class TimerId
{
public:
    TimerId()
        : timer_(nullptr),
          sequence_(0) {}

    TimerId(Timer *timer, int64_t seq)
        : timer_(timer),
          sequence_(seq) {}

    friend class TimerQueue;
private:
    Timer *timer_;  //timer对象
    int64_t sequence_; // timer的序号
};