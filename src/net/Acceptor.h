#pragma once

#include "Channel.h"
#include "Socket.h"
#include "base/noncopyable.h"

#include <functional>

class EventLoop;
class InetAddress;

class Acceptor : noncopyable
{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress &)>;

    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback &cb) { newConnectionCallback_ = cb; }

    bool listening() const { return listening_; }
    void listen();

private:
    void handleRead();

    EventLoop *loop_; // Acceptor�õľ����û�������Ǹ�baseLoop Ҳ����mainLoop
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectionCallback newConnectionCallback_;   //�������ӳɹ�ʱ�Ļص�����
    bool listening_;
    // int idleFd_;
};