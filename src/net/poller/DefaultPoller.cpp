#include"../Poller.h"
#include"EPollPoller.h"

#include <stdlib.h>

//¹¤³§º¯Êý
Poller* Poller::newDefaultPoller(EventLoop* loop)
{
    if(::getenv("USE_POLL"))
    {
        return nullptr;
    } else if(::getenv("USE_SELECT"))
    {
        return nullptr;
    } else {
        return new EPollPoller(loop);
    }
}