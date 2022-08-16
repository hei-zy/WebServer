#include "src/base/Timestamp.h"
#include "src/base/noncopyable.h"

#include <functional>
#include <atomic>

class Timer : noncopyable
{
public:
    using TimerCallback = std::function<void()>;

    Timer(TimerCallback cb, Timestamp when, double interval)
        : callback_(std::move(cb)),
          expiration_(when),
          interval_(interval),
          repeat_(interval > 0.0),
          sequence_(++s_numCreated_),
          canceled_(false) {}

    void run() const
    {
        callback_();
    }

    Timestamp expiration() const { return expiration_; }
    bool repeat() const { return repeat_; }
    int64_t sequence() const { return sequence_; }

    void restart(Timestamp now);

    static int64_t numCreated() { return s_numCreated_.load(); }

    void cancel() { canceled_ = true; }

    bool canceled() const { return canceled_; }

private:
    const TimerCallback callback_; //��ʱ���ص�����
    Timestamp expiration_;         //��һ�γ�ʱʱ��
    const double interval_;        //��ʱʱ�����������һ���Զ�ʱ�������ֵΪ0
    const bool repeat_;            //�Ƿ��ظ�
    const int64_t sequence_;       //��ʱ�����

    std::atomic_bool canceled_;     //�ö�ʱ���Ƿ�ɾ��

    static std::atomic_int s_numCreated_; //ȫ�ֶ�ʱ����������ǰ�Ѵ����Ķ�ʱ������
};