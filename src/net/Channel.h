#pragma once

#include <functional>
#include <memory>

#include "../base/noncopyable.h"
#include "../base/Timestamp.h"

class EventLoop;

// ChannelΪͨ������װfd�������Ȥ���¼�event ��EPOLLIN��EPOLLOUT�¼�����poller���ص��¼�

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    // fd�õ�Poller֪ͨ�Ժ� �����¼�����EventLoop::loop()�е���
    void handleEvent(Timestamp receiveTime);

    // ���ûص���������
    void setReadCallback(ReadEventCallback cb) { readCallback_=std::move(cb);}
    void setWriteCallback(EventCallback cb) { writeCallback_=std::move(cb);}
    void setCloseCallback(EventCallback cb) { closeCallback_=std::move(cb);}
    void setErrorCallback(EventCallback cb) { errorCallback_=std::move(cb);}

    // ��ֹ��channel�Ѿ���remove��connection�ѶϿ����� channel����ִ�лص�����
    void tie(const std::shared_ptr<void>&);

    int fd() const {return fd_;}
    int events() const {return events_;}

    void set_revents(int revent) { revents_=revent;}    //poller�������ط�������ʵ�¼�

    // ����fd_�¼����ͣ�ͨ������update()���£�
    void enableReading() {events_|=kReadEvent; update();}
    void disableReading() {events_ &= ~kReadEvent; update();}
    void enableWriting() {events_ |= kWriteEvent; update();}
    void disableWriting() {events_ &= ~kWriteEvent; update();}
    void disableAll() { events_ = kNoneEvent; update();}

    // ����fd_��ǰ�¼�����
    bool isNoneEvent() const { return events_ == kNoneEvent;}
    bool isWriting() const { return events_ & kWriteEvent;}
    bool isReading() const { return events_ & kReadEvent;}

    // fd_��Poller��������״̬
    int index() { return index_;}
    void set_index(int idx) {index_=idx;}

    // one loop per thread
    EventLoop *ownerLoop() { return loop_;}

    //����eventsToString()
    std::string reventsToString() const;
    std::string eventsToString() const;

    void remove(); //ɾ��Channel->����EventLoop�е�removeChannel->����poller�е�removeChannel
private:
    static std::string eventsToString(int fd, int ev);

    void update();  //����Channel�ϵ��¼�->����EventLoop�е�updateChannel->����poller�е�updateChannel
    void handleEventWithGuard(Timestamp receiveTime);   //��handleEvent�ڼ�����Ӵ��ں����

    static const int kNoneEvent;    //û���¼�
    static const int kReadEvent;    //���¼�
    static const int kWriteEvent;   //д�¼�

    EventLoop *loop_;   //channel����EventLoop����
    const int fd_;      //Poller���������ļ�������
    int events_;        //ע��fd����Ȥ�¼�
    int revents_;       //Poller���صľ��巢�����¼�
    int index_;         //�¼�������
                        //1����PollPoller�б�ʾ�¼���Poller���������
                        //2����EPollPoller�б�ʾ�¼�״̬��kNew,kAdded,kDeleted��
                        //��Ϊepoll�������ڲ��������ֻ���ؾ����¼�������Ҫ�Լ����������¼�����

    std::weak_ptr<void> tie_;   //��������Ƿ�Ͽ���TCPConnection�����Ƿ�������
    bool tied_;

    bool eventHanding_;     //�Ƿ�����ִ�лص�
    bool addedToLoop_;      //�Ƿ���Loop��

    //�¼��ص�������������fd_���巢�����¼�revents_�����ø��¼��Ļص�
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};