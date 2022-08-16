#include "EPollPoller.h"

#include "../../base/Logging.h"
#include "../Channel.h"

#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>

namespace
{
    const int kNew = -1;    //�µ�channel��δ����ӵ�Poller�У�channel��index_��ʼ��Ϊ-1
    const int kAdded = 1;   //��channel�Ѿ�����ӵ�Poller��
    const int kDeleted = 2; //ĳ��channel�Ѿ���Pollerɾ��
}

EPollPoller::EPollPoller(EventLoop *loop)
    : Poller(loop),
      epollfd_(::epoll_create1(EPOLL_CLOEXEC)), // EPOLL_CLOEXEC��fork���ӽ����дӸ���ĵõ���fd��exc���Զ��رգ���close-on-exec
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

//����epoll_wait
Timestamp EPollPoller::poll(int timeoutMs, ChannelList *activeChannels)
{
    LOG_TRACE << "fd total count" << channels_.size();
    int numEvents = ::epoll_wait(epollfd_, &*events_.begin(), static_cast<int>(events_.size()), timeoutMs);
    int savedErrno = errno; //�����errno
    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        LOG_TRACE << numEvents << "events happened";
        fillActiveChannels(numEvents, activeChannels);
        if (static_cast<size_t>(numEvents) == events_.size())
        {
            events_.resize(events_.size() * 2); // events_����
        }
    }
    else if (numEvents == 0)
    {
        LOG_TRACE << "nothing happened";
    }
    else
    {
        if (savedErrno == EINTR) //���ж�
        {
            errno = savedErrno;
            LOG_SYSERR << "EPollPoller::poll() EINTR";
        }
    }
    return now;
}

//��activeChannels������Ծ��channel��ͨ��������epoll_event.data.ptr���channelָ��
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

//����epoll_ctl
void EPollPoller::updateChannel(Channel* channel) 
{
    assertInLoopThread();
    const int index=channel->index();
    LOG_TRACE<<"fd = "<<channel->fd()<<" events ="<<channel->events()<<" index = "<<index;
    if(index == kNew || index == kDeleted) 
    {
        int fd=channel->fd();
        if (index == kNew) // �µ�channel����������������
        {
            assert(channels_.find(fd)==channels_.end());
            channels_[fd]=channel;
        }
        else // index==kDeleted �ж�channel�Ƿ�ɾ���ɾ�����fd��û��ָ����channel
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
        //�����channel��û�м����¼���ɾ����channel
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

//ɾ����channel(channels_��ɾ����������channel->index_==kNew)
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