#pragma once

#include <vector>
#include <sys/epoll.h>

#include "../../base/Timestamp.h"
#include "../Poller.h"

class Channel;

class EPollPoller : public Poller
{
public:
    EPollPoller(EventLoop *loop);
    ~EPollPoller() override;

    Timestamp poll(int timeoutMs, ChannelList *activeChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;

private:
    //向activeChannels中填充活跃的channel
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    //更新指定Channel上监听事件类型，本质上调用epoll_ctl
    void update(int operation, Channel *Channel);

    static const int kInitEventListSize = 16; // events_的初始容量
    static const char *operationToString(int op);   //输出op对应字符串，输出日志时使用

    using EventList = std::vector<epoll_event>;

    int epollfd_;      // epoll_create创建返回的fd
    EventList events_; //存放epoll_wait返回的所有就绪事件的文件描述符事件集合
    //父类中protected成员的Channels_(ChannelMap)
};