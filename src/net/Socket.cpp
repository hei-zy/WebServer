#include "Socket.h"
#include "InetAddress.h"
#include "base/Logging.h"

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

Socket::~Socket()
{
    close(sockfd_);
}

void Socket::bindAddress(const InetAddress &localaddr)
{
    if (0 > bind(sockfd_, reinterpret_cast<sockaddr *>(const_cast<sockaddr_in *>(localaddr.getSockAddr())), sizeof(sockaddr_in)))
    {
        LOG_SYSFATAL << "sockets::listenOrDie";
    }
}

void Socket::listen()
{
    int ret = ::listen(sockfd_, SOMAXCONN);
    if (ret < 0)
    {
        LOG_SYSFATAL << "sockets::listenOrDie";
    }
}

int Socket::accept(InetAddress *peeraddr)
{
    /**
     * accept4 直接设置socketfd属性（SOCK_NONBLOCK | SOCK_CLOEXEC）
     * Reactor模型 one loop per thread
     * poller + non-blocking IO
     **/
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    memset(&addr, 0, sizeof(addr));
    int connfd = accept4(sockfd_, reinterpret_cast<sockaddr *>(&addr), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd >= 0)
    {
        peeraddr->setSockAddr(addr);
    }
    else
    {
        int savedErrno = errno;
        LOG_SYSERR << "Socket::accept" << savedErrno;
    }
    return connfd;
}

void Socket::shutdownWrite()
{
    if (shutdown(sockfd_, SHUT_WR) < 0)
    {
        LOG_SYSERR << "sockets::shutdownWrite";
    }
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof(optval))); // TCP_NODELAY包含头文件 <netinet/tcp.h>
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof(optval))); // TCP_NODELAY包含头文件 <netinet/tcp.h>
}

void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof(optval))); // TCP_NODELAY包含头文件 <netinet/tcp.h>
}

void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof(optval))); // TCP_NODELAY包含头文件 <netinet/tcp.h>
}