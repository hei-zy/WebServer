#pragma once

#include <functional>
#include <memory>

#include "../base/noncopyable.h"
#include "../base/Timestamp.h"

class EventLoop;

// Channel为通道，封装fd与其感兴趣的事件event 如EPOLLIN、EPOLLOUT事件，与poller返回的事件

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(Timestamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    // fd得到Poller通知以后 处理事件，在EventLoop::loop()中调用
    void handleEvent(Timestamp receiveTime);

    // 设置回调函数对象
    void setReadCallback(ReadEventCallback cb) { readCallback_=std::move(cb);}
    void setWriteCallback(EventCallback cb) { writeCallback_=std::move(cb);}
    void setCloseCallback(EventCallback cb) { closeCallback_=std::move(cb);}
    void setErrorCallback(EventCallback cb) { errorCallback_=std::move(cb);}

    // 防止当channel已经被remove（connection已断开）， channel还在执行回调操作
    void tie(const std::shared_ptr<void>&);

    int fd() const {return fd_;}
    int events() const {return events_;}

    void set_revents(int revent) { revents_=revent;}    //poller用来返回发生的真实事件

    // 设置fd_事件类型（通过调用update()更新）
    void enableReading() {events_|=kReadEvent; update();}
    void disableReading() {events_ &= ~kReadEvent; update();}
    void enableWriting() {events_ |= kWriteEvent; update();}
    void disableWriting() {events_ &= ~kWriteEvent; update();}
    void disableAll() { events_ = kNoneEvent; update();}

    // 返回fd_当前事件类型
    bool isNoneEvent() const { return events_ == kNoneEvent;}
    bool isWriting() const { return events_ & kWriteEvent;}
    bool isReading() const { return events_ & kReadEvent;}

    // fd_在Poller的索引或状态
    int index() { return index_;}
    void set_index(int idx) {index_=idx;}

    // one loop per thread
    EventLoop *ownerLoop() { return loop_;}

    //调用eventsToString()
    std::string reventsToString() const;
    std::string eventsToString() const;

    void remove(); //删除Channel->调用EventLoop中的removeChannel->调用poller中的removeChannel
private:
    static std::string eventsToString(int fd, int ev);

    void update();  //更新Channel上的事件->调用EventLoop中的updateChannel->调用poller中的updateChannel
    void handleEventWithGuard(Timestamp receiveTime);   //由handleEvent在检查连接存在后调用

    static const int kNoneEvent;    //没有事件
    static const int kReadEvent;    //读事件
    static const int kWriteEvent;   //写事件

    EventLoop *loop_;   //channel所属EventLoop对象
    const int fd_;      //Poller监听对象。文件描述符
    int events_;        //注册fd感兴趣事件
    int revents_;       //Poller返回的具体发生的事件
    int index_;         //事件索引：
                        //1、在PollPoller中表示事件在Poller数组的索引
                        //2、在EPollPoller中表示事件状态（kNew,kAdded,kDeleted）
                        //因为epoll利用其内部红黑树，只返回就绪事件，不需要自己建立就绪事件数组

    std::weak_ptr<void> tie_;   //检测连接是否断开（TCPConnection对象是否析构）
    bool tied_;

    bool eventHanding_;     //是否正在执行回调
    bool addedToLoop_;      //是否在Loop中

    //事件回调函数对象。依据fd_具体发生的事件revents_，调用该事件的回调
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};