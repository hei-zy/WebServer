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

    //�̰߳�ȫ---runInLoop()
    TimerId addTimer(TimerCallback cb,
                     Timestamp when,
                     double interval);
    //�̰߳�ȫ---runInLoop()
    void cancel(TimerId timerId);

private:
    using Entry = std::pair<Timestamp, Timer *>;                                           //��ʱ������Timestamp,Timer*��
    using TimerList = std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>>; //��Сʱ���
    using ActiveTimer = std::pair<Timer *, int64_t>;                                       // cancelʱʹ��
    using ActiveTimerSet = std::set<ActiveTimer>;                                          // cancelʱʹ��

    // ���г�Ա����ֻ��������������I/O�߳��е��ã����Բ��ü�����̫����������ή�ͷ����������ܣ�
    void addTimerInLoop(Timer *timer);
    void cancelInLoop(TimerId timerId);
    // ��ʱ����ʱ�¼�����ʱ�Ļص�����
    void handleRead();
    //ȡ����ʱ��ʱ��
    std::vector<Entry> getExpired(Timestamp now);
    void reset(const std::vector<Entry> &expired, Timestamp now); //���ö�ʱ��������ö�ʱ���ǿ��ظ��ģ�timer->interval_!=0������������

    bool insert(Timer *timer); //�����µĶ�ʱ��

    EventLoop *loop_;
    const int timerfd_;      //��ʱ��fd
    Channel timerfdChannel_; //��ʱ��channel������loop�ϣ�������ʱ��timerfd_��ʱ�¼����ɶ�����һ��loopһ��timerfdChannel_
    //����ʱʱ�� �������еĶ�ʱ��ʱ��� ----����ɾ��
    TimerList timers_;
    size_t timersSize; // timers_�л�Ծtimer��

    // for cancel()
    ActiveTimerSet activeTimers_;
    std::atomic_bool callingExpiredTimers_;
    ActiveTimerSet cancelingTimers_; //��¼��ȡ���Ķ�ʱ�����������䱻���ã��������¼�����У�
};