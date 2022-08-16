#include "EPollPoller.h"

#include "../../base/Logging.h"
#include "../Channel.h"

#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace
{
    const int kNew = -1;    //新的channel还未被添加到Poller中，channel的index_初始化为-1
    const int kAdded = 1;   //该channel已经被添加到Poller中
    const int kDeleted = 2; //某个channel已经从Poller删除
}

EPollPoller::EPollPoller(EventLoop *loop)
    : Poller(loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)), // EPOLL_CLOEXEC，fork的子进程中从父类的得到的fd在exc后自动关闭，即close-on-exec
      events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG_SYSFATAL << "EPollPoller::EPollPoller";
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

//调用epoll_wait
Timestamp EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    LOG_TRACE << "fd total count" << channels_.size();
    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);
    int savedErrno = errno; //保存的errno
    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        LOG_TRACE << numEvents << "events happened";
        fillActiveChannels(numEvents, activeChannels);
        if (static_cast<size_t>(numEvents) == events_.size())
        {
            events_.resize(events_.size() * 2); // events_扩容
        }
    }
    else if (numEvents == 0)
    {
        LOG_TRACE << "nothing happened";
    }
    else
    {
        if (savedErrno == EINTR) //被中断
        {
            errno = savedErrno;
            LOG_SYSERR << "EPollPoller::poll() EINTR";
        }
    }
    return now;
}

//向activeChannels中填充活跃的channel，通过共用体epoll_event.data.ptr存放channel指针
void EPollPoller::fillActiveChannels(int numEvents, ChannelList* activeChannels) const
{
    assert(numEvents<=events_.size());
    for(int i=0;i<numEvents;++i) 
    {
        Channel* channel=static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->emplace_back(channel);
    }
}

//调用epoll_ctl
void EPollPoller::updateChannel(Channel* channel) 
{
    assertInLoopThread();
    const int index=channel->index();
    LOG_TRACE<<"fd = "<<channel->fd()<<" events ="<<channel->events()<<" index = "<<index;
    if(index == kNew || index == kDeleted) 
    {
        int fd=channel->fd();
        if (index == kNew) // 新的channel，将其加入监听集合
        {
            assert(channels_.find(fd)==channels_.end());
            channels_[fd]=channel;
        }
        else // index==kDeleted 判断channel是否删除干净，即fd有没有指向多个channel
        {
            assert(channels_.find(fd)!=channels_.end());
            assert(channels_[fd]==channel);
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD,channel);
    }
    else    //index==kAdded
    {
        int fd=channel->fd();
        (void)fd;
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] == channel);
        assert(index == kAdded);
        //如果该channel上没有监听事件，删除该channel
        if(channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else 
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

//删除该channel(channels_中删除，并更新channel->index_==kNew)
void EPollPoller::removeChannel(Channel* channel)
{
    int fd=channel->fd();
    LOG_TRACE<<"fd = "<<fd;
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    assert(channel->isNoneEvent());
    channels_.erase(fd);
    int index = channel->index();
    assert(index == kAdded || index == kDeleted);
    if (index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

void EPollPoller::update(int operation, Channel*channel)
{
    epoll_event event;
    ::memset(&event, 0, sizeof(event));
    int fd=channel->fd();
    event.events=channel->events();
    event.data.fd=fd;
    event.data.ptr=channel;
    LOG_TRACE << "epoll_ctl op = " << operationToString(operation)
              << " fd = " << fd << " event = { " << channel->eventsToString() << " }";
    if(::epoll_ctl(epollfd_,operation,fd,&event)<0)
    {
        if(operation==EPOLL_CTL_DEL)
        {
            if (operation == EPOLL_CTL_DEL)
            {
                LOG_SYSERR << "epoll_ctl op =" << operationToString(operation) << " fd =" << fd;
            }
            else
            {
                LOG_SYSFATAL << "epoll_ctl op =" << operationToString(operation) << " fd =" << fd;
            }
        }
    }
}

const char *EPollPoller::operationToString(int op)
{
    switch (op)
    {
    case EPOLL_CTL_ADD:
        return "ADD";
    case EPOLL_CTL_DEL:
        return "DEL";
    case EPOLL_CTL_MOD:
        return "MOD";
    default:
        assert(false && "ERROR op");
        return "Unknown Operation";
    }
}