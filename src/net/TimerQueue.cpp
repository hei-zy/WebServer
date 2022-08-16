#include "TimerQueue.h"
#include "src/base/Logging.h"
#include "EventLoop.h"
#include "Timer.h"
#include "TimerId.h"

#include <sys/timerfd.h>
#include <unistd.h>

//����һ��Timerfd�ļ�������
int createTimerfd()
{
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC,
                                   TFD_NONBLOCK | TFD_CLOEXEC);
    if (timerfd < 0)
    {
        LOG_SYSFATAL << "Failed in timerfd_create";
    }
    return timerfd;
}

//���㳬ʱʱ���뵱ǰʱ���ʱ���
timespec howMuchTimeFromNow(Timestamp when)
{
    int64_t microseconds = when.microSecondsSinceEpoch() - Timestamp::now().microSecondsSinceEpoch();
    if (microseconds < 100)
    {
        microseconds = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(
        microseconds / Timestamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(
        (microseconds % Timestamp::kMicroSecondsPerSecond) * 1000);
    return ts;
}

//���timefd�ϵĳ�ʱ�¼�������timerfd�е����ݶ�����
void readTimerfd(int timerfd, Timestamp now)
{
    uint64_t howmany;
    ssize_t n = ::read(timerfd, &howmany, sizeof howmany);
    LOG_TRACE << "TimerQueue::handleRead() " << howmany << " at " << now.toString();
    if (n != sizeof howmany)
    {
        LOG_ERROR << "TimerQueue::handleRead() reads " << n << " bytes instead of 8";
    }
}

//����timerfd�ϳ�ʱʱ�䣬��Ϊʱ�������Сֵ
void resetTimerfd(int timerfd, Timestamp expiration)
{
    // wake up loop by timerfd_settime()
    struct itimerspec newValue;
    struct itimerspec oldValue;
    ::memset(&newValue, 0, sizeof(newValue));
    ::memset(&oldValue, 0, sizeof(oldValue));
    newValue.it_value = howMuchTimeFromNow(expiration);
    int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
    if (ret)
    {
        LOG_SYSERR << "timerfd_settime()";
    }
}

TimerQueue::TimerQueue(EventLoop *loop)
    : loop_(loop),
      timerfd_(createTimerfd()),
      timerfdChannel_(loop, timerfd_),
      timers_(),
      timersSize(0),
      callingExpiredTimers_(false)
{
    //����timerfdChannel_�ɶ��¼��ص�����
    timerfdChannel_.setReadCallback(
        std::bind(&TimerQueue::handleRead, this));
    //��loop��ע��timerfd�ɶ��¼�
    timerfdChannel_.enableReading();
}

TimerQueue::~TimerQueue()
{
    timerfdChannel_.disableAll();
    timerfdChannel_.remove();
    ::close(timerfd_);
    // do not remove channel, since we're in EventLoop::dtor();
    while (!timers_.empty())
    {
        const Entry &timer = timers_.top();
        timers_.pop();
        delete timer.second;
    }
}

TimerId TimerQueue::addTimer(TimerCallback cb, Timestamp when, double interval)
{
    Timer *timer = new Timer(std::move(cb), when, interval);
    loop_->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));  //runInLoopʵ���̰߳�ȫ
    return TimerId(timer, timer->sequence());
}

void TimerQueue::cancel(TimerId timerId)
{
    loop_->runInLoop(std::bind(&TimerQueue::cancelInLoop, this, timerId));
}

void TimerQueue::addTimerInLoop(Timer *timer)
{
    loop_->assertInLoopThread();
    bool earliestChanged = insert(timer); //����һ����ʱ����
                                          //����µĶ�ʱ����ʱʱ���TimerList�����ж�ʱ���ĳ�ʱʱ��С������Ҫ��������Timefd��ʱʱ��
    if (earliestChanged)
    {
        resetTimerfd(timerfd_, timer->expiration()); //����timerfd�ĳ�ʱʱ��
    }
}

void TimerQueue::cancelInLoop(TimerId timerId)
{
    loop_->assertInLoopThread();
    assert(timersSize == activeTimers_.size());
    ActiveTimer timer(timerId.timer_, timerId.sequence_);
    ActiveTimerSet::iterator it = activeTimers_.find(timer);
    if (it != activeTimers_.end())
    {
        it->first->cancel();//����ɾ��
        --timersSize;
        activeTimers_.erase(it);
    }
    else if (callingExpiredTimers_)
    {
        cancelingTimers_.emplace(timer);
    }
    assert(timersSize == activeTimers_.size());
}

void TimerQueue::handleRead()
{
    loop_->assertInLoopThread();
    Timestamp now(Timestamp::now());
    readTimerfd(timerfd_, now);     //��timerfd�ϵĳ�ʱ�¼����������һֱ����
    std::vector<Entry> expired = getExpired(now);   //ȡ����ʱ��ʱ��
    callingExpiredTimers_ = true;
    cancelingTimers_.clear();
    // safe to callback outside critical section
    for (const Entry &it : expired)
    {
        it.second->run();
    }
    callingExpiredTimers_ = false;
    reset(expired, now); // ���ö�ʱ��,������resetTimerfd()����timerfd��ʱʱ��
}

std::vector<TimerQueue::Entry> TimerQueue::getExpired(Timestamp now)
{
    assert(timersSize == activeTimers_.size());
    std::vector<Entry> expired;
    while(!timers_.empty() && timers_.top().first<=now) {
        const Entry &it = timers_.top();
        timers_.pop();
        if (it.second->canceled())
        {
            delete it.second; //����ɾ����timer
        }
        else 
        {
            expired.emplace_back(it);
        }
    }
    for (const Entry &it : expired)
    {
        ActiveTimer timer(it.second, it.second->sequence());
        size_t n = activeTimers_.erase(timer);
        assert(n == 1);
        (void)n;
    }
    assert(timersSize == activeTimers_.size());
    return expired;
}

void TimerQueue::reset(const std::vector<Entry> &expired, Timestamp now)
{
    Timestamp nextExpire;

    for (const Entry &it : expired)
    {
        ActiveTimer timer(it.second, it.second->sequence());
        //������ظ��Ķ�ʱ��������δȡ���Ķ�ʱ�����������ö�ʱ��
        if (it.second->repeat() && cancelingTimers_.find(timer) == cancelingTimers_.end())
        {
            it.second->restart(now);
            insert(it.second);
        }
        else
        {
            //ɾ��һ���Զ�ʱ��
            delete it.second;
        }
    }
    if (!timers_.empty())
    {
        nextExpire = timers_.top().second->expiration();
    }

    if (nextExpire.valid())
    {
        resetTimerfd(timerfd_, nextExpire);
    }
}

bool TimerQueue::insert(Timer *timer)
{
    loop_->assertInLoopThread();
    assert(timersSize == activeTimers_.size());
    bool earliestChanged = false;
    Timestamp when = timer->expiration();
    //����µĶ�ʱ����ʱʱ���TimerList�����ж�ʱ���ĳ�ʱʱ��С������Ҫ��������Timefd��ʱʱ��
    if (timers_.empty() || when < timers_.top().first)
    {
        earliestChanged = true;
    }
    timers_.emplace(when, timer);
    ++timersSize;
    activeTimers_.emplace(timer, timer->sequence());
    assert(timersSize == activeTimers_.size());
    return earliestChanged;
}