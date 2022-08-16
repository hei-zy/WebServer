#include "Acceptor.h"

#include <base/Logging.h>
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"

#include <errno.h>
// #include <fcntl.h>
#include <unistd.h>

//����������socket
int createNonblockingOrDie(sa_family_t family)
{
    int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0)
    {
        LOG_SYSFATAL << "sockets::createNonblockingOrDie";
    }
    return sockfd;
}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
    : loop_(loop),
      acceptSocket_(createNonblockingOrDie(AF_INET)),
      acceptChannel_(loop, acceptSocket_.fd()),
      listening_(false)
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(reuseport);
    acceptSocket_.bindAddress(listenAddr);
    // TcpServer::start() => Acceptor.listen() ��������û����� Ҫִ��һ���ص�(accept => connfd => �����Channel => ����subloop)
    // baseloop���������¼����� => acceptChannel_(listenfd) => ִ�иûص�����
    acceptChannel_.setReadCallback(
        std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
    acceptChannel_.disableAll(); // �Ѵ�Poller�и���Ȥ���¼�ɾ����
    acceptChannel_.remove();     // ����EventLoop->removeChannel => Poller->removeChannel ��Poller��ChannelMap��Ӧ�Ĳ���ɾ��
}

void Acceptor::listen()
{
    loop_->assertInLoopThread();
    listening_ = true;
    acceptSocket_.listen();         // listen
    acceptChannel_.enableReading(); // acceptChannel_ע����Poller
}

// listenfd���¼����������������û�����
void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if (connfd >= 0)
    {
        if (newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr); // ��ѯ�ҵ�subLoop ���Ѳ��ַ���ǰ���¿ͻ��˵�Channel
        }
        else
        {
            ::close(connfd);
        }
    }
    else
    {
        LOG_SYSERR << "in Acceptor::handleRead";
    }
}