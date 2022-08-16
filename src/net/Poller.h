#pragma once

#include <vector>
#include <unordered_map>

#include "../base/noncopyable.h"
#include "../base/Timestamp.h"
#include"EventLoop.h"

class Channel;
class EventLoop;

//虚基类-多路事件分发器中的核心IO复用模块，封装epoll_wait与epoll_ctl等功能
class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel*>;  //存放就绪Channel集合

    //静态工厂函数，创建新的Poller（在DefaultPoller.cpp文件中实现）
    static Poller *newDefaultPoller(EventLoop *loop);

    Poller(EventLoop*loop);
    virtual ~Poller();
    
    //封装epoll_wait功能，返回就绪事件集合。在Loop循环中调用
    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;

    //封装epoll_ctl的EPOLL_CTL_ADD与EPOLL_CTL_MOD功能，更新该Channel事件类型
    virtual void updateChannel(Channel* channel)=0;

    //封装epoll_ctl的EPOLL_CTL_DEL功能,从监听的Channel集合中删除目标Channel
    virtual void removeChannel(Channel* channel)=0;

    //判断参数channel是否在当前的Poller当中
    virtual bool hasChannel(Channel* channel) const;

    void assertInLoopThread() const
    {
        ownerLoop_->assertInLoopThread();
    }

protected:
    using ChannelMap=std::unordered_map<int,Channel*>;
    ChannelMap channels_;   //存放该Poller监听的Channel*,通过key值（文件描述符）索引channel;
private:
    EventLoop* ownerLoop_;  //one loop one poller，定义Poller所属事件循环EventLoop
};