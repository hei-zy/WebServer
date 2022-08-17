#include "EventLoop.h"
#include "src/base/Logging.h"
#include "Channel.h"
#include "Poller.h"
#include "Socket.h"
#include "TimerQueue.h"

#include <algorithm>
#include <sys/eventfd.h>
#include <unistd.h>

// ��ֹһ���̴߳������EventLoop
__thread EventLoop *t_loopInThisThread = nullptr;

// ����Ĭ�ϵ�Poller IO���ýӿڵĳ�ʱʱ��
const int kPollTimeMs = 10000; // 10000���� = 10����

/* �����߳�֮�����̺߳����߳�˭�������ǲ�ȷ���ġ�
 * ͨ��һ��eventfd���߳�֮�䴫�����ݵĺô��Ƕ���߳����������Ϳ���ʵ��ͬ����
 * eventfd֧�ֵ�����ں˰汾ΪLinux 2.6.27,��2.6.26��֮ǰ�İ汾Ҳ����ʹ��eventfd������flags��������Ϊ0��
 * ����ԭ�ͣ�
 *     #include <sys/eventfd.h>
 *     int eventfd(unsigned int initval, int flags);
 * ����˵����
 *      initval,��ʼ����������ֵ��
 *      flags, EFD_NONBLOCK,����socketΪ��������
 *             EFD_CLOEXEC��ִ��fork��ʱ���ڸ������е����������Զ��رգ��ӽ����е�������������
 * ������
 *     eventfd��������ͬһ������֮�е��߳�֮���ͨ�š�
 *     eventfd����������ͬ��Ե��ϵ�Ľ���֮���ͨ�š�
 *     eventfd���ڲ�ͬ��Ե��ϵ�Ľ���֮��ͨ�ŵĻ���Ҫ��eventfd���ڼ������̹���Ĺ����ڴ��С�
 */
// ����wakeupfd ����notify����subReactor����������channel
int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        LOG_SYSERR << "Failed in eventfd";
        abort();
    }
    return evtfd;
}

EventLoop::EventLoop()
    : looping_(false),
      quit_(false),
      eventHandling_(false),
      callingPendingFunctors_(false),
      threadId_(CurrentThread::tid()),
      poller_(Poller::newDefaultPoller(this)),
      timerQueue_(new TimerQueue(this)),
      wakeupFd_(createEventfd()),
      wakeupChannel_(new Channel(this, wakeupFd_)),
      currentActiveChannel_(NULL)
{
    LOG_DEBUG << "EventLoop created " << this << " in thread " << threadId_;
    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread
                  << " exists in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
    wakeupChannel_->setReadCallback([this](Timestamp t)
                                    { this->handleRead(); });

    // wakeupChannel_->setReadCallback(
    //     std::bind(&EventLoop::handleRead, this)); // ����wakeupfd���¼������Լ������¼���Ļص�����
    wakeupChannel_->enableReading();              // ÿһ��EventLoop��������wakeupChannel_��EPOLL���¼�
}

EventLoop::~EventLoop()
{
    LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
              << " destructs in thread " << CurrentThread::tid();
    wakeupChannel_->disableAll(); // ��wakeupChannel_�Ƴ����и���Ȥ���¼�
    wakeupChannel_->remove();     // ��wakeupChannel_��EventLoop��ɾ����
    ::close(wakeupFd_);
    t_loopInThisThread = NULL;
}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;
    LOG_TRACE << "EventLoop " << this << " start looping";
    while (!quit_)
    {
        activeChannels_.clear();
        pollReturnTime_ = poller_->poll(kPollTimeMs, &activeChannels_);
        eventHandling_ = true;
        for (Channel *channel : activeChannels_)
        {
            // Poller������Щchannel�������¼� Ȼ���ϱ���EventLoop ֪ͨchannel������Ӧ���¼�(������Ӧ�Ļص�����)
            currentActiveChannel_ = channel;
            currentActiveChannel_->handleEvent(pollReturnTime_);
        }
        currentActiveChannel_ = NULL;
        eventHandling_ = false;
        /**
         * ִ�е�ǰEventLoop�¼�ѭ����Ҫ����Ļص����� �����߳��� >=2 ����� IO�߳� mainloop(mainReactor) ��Ҫ������
         * accept�������� => ��accept���ص�connfd���ΪChannel => TcpServer::newConnectionͨ����ѯ��TcpConnection��������subloop����
         *
         * mainloop����queueInLoop���ص�����subloop���ûص���Ҫsubloopִ�� ��subloop����poller_->poll�������� queueInLoopͨ��wakeup��subloop����
         **/
        doPendingFunctors();
    }
    LOG_TRACE << "EventLoop " << this << " stop looping";
    looping_ = false;
}

/**
 * �˳��¼�ѭ��
 * 1. ���loop���Լ����߳��е���quit�ɹ��� ˵����ǰ�߳��Ѿ�ִ�������loop()������poller_->poll���˳�
 * 2. ������ǵ�ǰEventLoop�����߳��е���quit�˳�EventLoop ��Ҫ����EventLoop�����̵߳�epoll_wait
 *
 * ������һ��subloop(worker)�е���mainloop(IO)��quitʱ ��Ҫ����mainloop(IO)��poller_->poll ����ִ����loop()����
 *
 * ������ ע�⣺ ��������� mainloop������������ ���ص�д��subloop�� ͨ��������������ģ�ͼ���ʵ���̰߳�ȫ�Ķ���
 * ������       ����muduoͨ��wakeup()���� ʹ��eventfd������wakeupFd_ notify ʹ��mainloop��subloop֮���ܹ�����ͨ��
 **/
void EventLoop::quit()
{
    quit_ = true;
    if (!isInLoopThread())
    {
        wakeup();
    }
}

// �ڵ�ǰloop��ִ��cb
void EventLoop::runInLoop(Functor cb)
{
    if (isInLoopThread()) // ��ǰEventLoop��ִ�лص�
    {
        cb();
    }
    else // �ڷǵ�ǰEventLoop�߳���ִ��cb������Ҫ����EventLoop�����߳�ִ��cb
    {
        queueInLoop(std::move(cb));
    }
}

// ��cb��������� ����loop���ڵ��߳�ִ��cb
void EventLoop::queueInLoop(Functor cb)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        pendingFunctors_.push_back(std::move(cb));
    }
    /**
     * || callingPendingFunctors����˼�� ��ǰloop����ִ�лص��� ����loop��pendingFunctors_���ּ������µĻص� ��Ҫͨ��wakeupд�¼�
     * ������Ӧ����Ҫִ������ص�������loop���߳� ��loop()��һ��poller_->poll()���������������Ļ����ӳ�ǰһ���¼���Ļص���ִ�У���Ȼ��
     * ����ִ��pendingFunctors_�еĻص�����
     **/
    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup(); // ����loop�����߳�
    }
}

// ��������loop�����߳� ��wakeupFd_дһ������ wakeupChannel�ͷ������¼� ��ǰloop�߳̾ͻᱻ����
void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof(one));
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

//��wakeupfd_�е����ݣ���wakeup()����ʹ��
void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof(one));
    if (n != sizeof one)
    {
        LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
}

// ����Poller_->updateChannel()�ķ���
void EventLoop::updateChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

// ����Poller_->removeChannel()�ķ���
void EventLoop::removeChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    if (eventHandling_)
    {
        //��channel�Ƿ������¼�����
        assert(currentActiveChannel_ == channel ||
               std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());
    }
    poller_->removeChannel(channel);
}

// ����Poller_->hasChannel()�ķ���
bool EventLoop::hasChannel(Channel *channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    return poller_->hasChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
    LOG_FATAL << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << " was created in threadId_ = " << threadId_
              << ", current thread id = " << CurrentThread::tid();
}

void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        //ͨ��swap()��pendingFunctors_�����ֲ�������
        // 1����С�ٽ������ȣ�2�����Բ������������̵߳���queueInLoop()��
        std::lock_guard<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }
    for (const Functor &functor : functors)
    {
        functor(); // ִ�е�ǰloop��Ҫִ�еĻص�����
    }
    callingPendingFunctors_ = false;
}

size_t EventLoop::queueSize() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return pendingFunctors_.size();
}

TimerId EventLoop::runAt(Timestamp time, TimerCallback cb)
{
    return timerQueue_->addTimer(std::move(cb), time, 0.0);
}

TimerId EventLoop::runAfter(double delay, TimerCallback cb)
{
    Timestamp time(addTime(Timestamp::now(), delay));
    return runAt(time, std::move(cb));
}

TimerId EventLoop::runEvery(double interval, TimerCallback cb)
{
    Timestamp time(addTime(Timestamp::now(), interval));
    return timerQueue_->addTimer(std::move(cb), time, interval);
}

void EventLoop::cancel(TimerId timerId)
{
    return timerQueue_->cancel(timerId);
}