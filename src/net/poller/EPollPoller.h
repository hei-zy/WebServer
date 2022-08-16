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
    //��activeChannels������Ծ��channel
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;
    //����ָ��Channel�ϼ����¼����ͣ������ϵ���epoll_ctl
    void update(int operation, Channel *Channel);

    static const int kInitEventListSize = 16; // events_�ĳ�ʼ����
    static const char *operationToString(int op);   //���op��Ӧ�ַ����������־ʱʹ��

    using EventList = std::vector<epoll_event>;

    int epollfd_;      // epoll_create�������ص�fd
    EventList events_; //���epoll_wait���ص����о����¼����ļ��������¼�����
    //������protected��Ա��Channels_(ChannelMap)
};