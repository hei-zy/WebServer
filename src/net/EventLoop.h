#pragma once

#include "src/base/CurrentThread.h"
#include "src/base/Timestamp.h"
#include "src/base/noncopyable.h"
#include "TimerId.h"

#include <vector>
#include <atomic>
#include <mutex>
#include <memory>
#include <functional>

class Channel;
class Poller;
class TimerQueue;

class EventLoop : noncopyable
{
public:
    using Functor = std::function<void()>;
    using TimerCallback = std::function<void()>;

    EventLoop();
    ~EventLoop();

    // �����¼�ѭ��
    void loop();
    // �˳��¼�ѭ��(quit_=true)
    void quit();

    Timestamp pollReturnTime() const { return pollReturnTime_; }

    // �ɿ��̵߳���,�ڵ�ǰloop��IO�̣߳���ֱ��ִ��cb���������queueInLoop()
    void runInLoop(Functor cb);
    // ���ϲ�ע��Ļص�����cb��������� ����loop���ڵ��߳�ִ��cb
    void queueInLoop(Functor cb);

    size_t queueSize() const; //����pendingFunctors_�лص�����������

    // timers------------------------------------------------------
    //  ʹ�ö�ʱ��
    TimerId runAt(Timestamp time, TimerCallback cb);

    //ʹ�ö�ʱ��---��һ��ʱ���
    TimerId runAfter(double delay, TimerCallback cb);

    // ʹ�ö�ʱ��---���ظ�
    TimerId runEvery(double interval, TimerCallback cb);

    ///ͨ��timerIdȡ����ʱ��
    void cancel(TimerId timerId);

    // ͨ����wakeupFd_(eventfd)��дһ�����ݣ�����loop���ڵ��߳�
    void wakeup();

    // EventLoop�ķ��� => Poller�ķ���
    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    void assertInLoopThread()
    {
        if (!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    // �ж�EventLoop�����Ƿ����Լ����߳���
    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); } // threadId_ΪEventLoop����ʱ���߳�id CurrentThread::tid()Ϊ��ǰ�߳�id

    static EventLoop *getEventLoopOfCurrentThread();

private:
    void abortNotInLoopThread();
    void handleRead();        // ��eventfd���ص��ļ�������wakeupFd_�󶨵��¼��ص� ��wakeup()ʱ �����¼�����ʱ ����handleRead()��wakeupFd_��8�ֽ� ͬʱ����������epoll_wait
    void doPendingFunctors(); // ִ���ϲ�ص���ͨ��swap()��pendingFunctors_�����ֲ�������
                              // 1����С�ٽ������ȣ�2�����Բ������������̵߳���queueInLoop()��

    using ChannelList = std::vector<Channel *>;

    std::atomic_bool looping_;                //�Ƿ���loop()
    std::atomic_bool quit_;                   // ��ʶ�˳�loopѭ��
    std::atomic_bool eventHandling_;          //  �Ƿ��ڴ����¼�
    std::atomic_bool callingPendingFunctors_; //�Ƿ��ڴ���pendingFunctors_

    const pid_t threadId_; // ��¼��ǰEventLoop�Ǳ��ĸ��߳�id������ ����ʶ�˵�ǰEventLoop�������߳�id

    Timestamp pollReturnTime_; // Poller���ط����¼���Channels��ʱ���

    std::unique_ptr<Poller> poller_;
    std::unique_ptr<TimerQueue> timerQueue_; //��ʱ��������addtimer(),cancel()

    int wakeupFd_; // ��mainLoop��ȡһ�����û���Channel ��ͨ����ѯ�㷨ѡ��һ��subLoop ͨ���ó�Ա����subLoop����Channel
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_; // ����Poller��⵽��ǰ���¼�����������Channel�б�
    Channel *currentActiveChannel_;

    mutable std::mutex mutex_;             // ������ ��������pendingFunctors_���̰߳�ȫ����
    std::vector<Functor> pendingFunctors_; // �洢loop��Ҫִ�е����лص��������������
};