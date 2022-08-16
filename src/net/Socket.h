#pragma once

#include "base/noncopyable.h"

class InetAddress;

//��װsocket�ļ���������ز���������ʱ�ر��ļ�������
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

    void shutdownWrite();   //shutdown() SHUT_WR �ر�socketfdд�ˣ����Ӵ��ڰ�ر�״̬

    void setTcpNoDelay(bool on);    //TCP_NODELAY ��ֹ������Nagle�㷨(Nagleӵ�������㷨���ŵ���ֻ�������һ��С��)
    void setReuseAddr(bool on);     //SO_REUSEADDR
    void setReusePort(bool on);     //SO_REUSEPORT
    void setKeepAlive(bool on);     //SO_KEEPALIVE  �Ƿ��ͱ����

private:
    const int sockfd_;
};