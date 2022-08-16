#pragma once

#include "base/noncopyable.h"

class InetAddress;

//封装socket文件描述符相关操作，析构时关闭文件描述符
class Socket : noncopyable
{
public:
    explicit Socket(int sockfd)
        : sockfd_(sockfd) {}

    ~Socket();

    int fd() const { return sockfd_; }
    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);

    void shutdownWrite();   //shutdown() SHUT_WR 关闭socketfd写端，连接处于半关闭状态

    void setTcpNoDelay(bool on);    //TCP_NODELAY 禁止或启动Nagle算法(Nagle拥塞控制算法：信道中只允许存在一个小包)
    void setReuseAddr(bool on);     //SO_REUSEADDR
    void setReusePort(bool on);     //SO_REUSEPORT
    void setKeepAlive(bool on);     //SO_KEEPALIVE  是否发送保活报文

private:
    const int sockfd_;
};