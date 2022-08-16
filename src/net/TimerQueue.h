#include "src/base/Timestamp.h"
#include "Channel.h"
#include "src/base/noncopyable.h"

#include <vector>
#include <queue>
#include<atomic>
#include<set>

class Timer;
class TimerId;
class EventLoop;

class TimerQueue : noncopyable
{
public:
    using TimerCallback = std::function<void()>;

    explicit TimerQueue(EventLoop *loop);
    ~TimerQueue();

    //线程安全---runInLoop()
    TimerId addTimer(TimerCallback cb,
                     Timestamp when,
                     double interval);
    //线程安全---runInLoop()
    void cancel(TimerId timerId);

private:
    using Entry = std::pair<Timestamp, Timer *>;                                           //定时器对象（Timestamp,Timer*）
    using TimerList = std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>>; //最小时间堆
    using ActiveTimer = std::pair<Timer *, int64_t>;                                       // cancel时使用
    using ActiveTimerSet = std::set<ActiveTimer>;                                          // cancel时使用

    // 下列成员函数只可能在其所属的I/O线程中调用，所以不用加锁（太多的锁竞争会降低服务器的性能）
    void addTimerInLoop(Timer *timer);
    void cancelInLoop(TimerId timerId);
    // 定时器超时事件发生时的回调函数
    void handleRead();
    //取出超时定时器
    std::vector<Entry> getExpired(Timestamp now);
    void reset(const std::vector<Entry> &expired, Timestamp now); //重置定时器，如果该定时器是可重复的（timer->interval_!=0），就绪重置

    bool insert(Timer *timer); //插入新的定时器

    EventLoop *loop_;
    const int timerfd_;      //定时器fd
    Channel timerfdChannel_; //定时器channel，绑定在loop上，监听定时器timerfd_超时事件（可读），一个loop一个timerfdChannel_
    //按超时时间 升序排列的定时器时间堆 ----惰性删除
    TimerList timers_;
    size_t timersSize; // timers_中活跃timer数

    // for cancel()
    ActiveTimerSet activeTimers_;
    std::atomic_bool callingExpiredTimers_;
    ActiveTimerSet cancelingTimers_; //记录被取消的定时器，（避免其被重置，导致重新加入队列）
};