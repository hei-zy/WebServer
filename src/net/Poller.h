#pragma once

#include <vector>
#include <unordered_map>

#include "../base/noncopyable.h"
#include "../base/Timestamp.h"
#include"EventLoop.h"

class Channel;
class EventLoop;

//�����-��·�¼��ַ����еĺ���IO����ģ�飬��װepoll_wait��epoll_ctl�ȹ���
class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;  //��ž���Channel����

    //��̬���������������µ�Poller����DefaultPoller.cpp�ļ���ʵ�֣�
    static Poller *newDefaultPoller(EventLoop *loop);

    Poller(EventLoop*loop);
    virtual ~Poller();
    
    //��װepoll_wait���ܣ����ؾ����¼����ϡ���Loopѭ���е���
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    //��װepoll_ctl��EPOLL_CTL_ADD��EPOLL_CTL_MOD���ܣ����¸�Channel�¼�����
    virtual void updateChannel(Channel* channel)=0;

    //��װepoll_ctl��EPOLL_CTL_DEL����,�Ӽ�����Channel������ɾ��Ŀ��Channel
    virtual void removeChannel(Channel* channel)=0;

    //�жϲ���channel�Ƿ��ڵ�ǰ��Poller����
    virtual bool hasChannel(Channel* channel) const;

    void assertInLoopThread() const
    {
        ownerLoop_->assertInLoopThread();
    }

protected:
    using ChannelMap=std::unordered_map<int,Channel*>;
    ChannelMap channels_;   //��Ÿ�Poller������Channel*,ͨ��keyֵ���ļ�������������channel;
private:
    EventLoop* ownerLoop_;  //one loop one poller������Poller�����¼�ѭ��EventLoop
};