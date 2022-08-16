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
    const TimerCallback callback_; //定时器回调函数
    Timestamp expiration_;         //下一次超时时间
    const double interval_;        //超时时间间隔，如果是一次性定时器，则该值为0
    const bool repeat_;            //是否重复
    const int64_t sequence_;       //定时器序号

    std::atomic_bool canceled_;     //该定时器是否被删除

    static std::atomic_int s_numCreated_; //全局定时器计数，当前已创建的定时器数量
};