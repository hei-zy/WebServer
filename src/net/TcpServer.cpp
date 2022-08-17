#include "TcpServer.h"
#include "EventLoop.h"
#include "EventLoopThreadPool.h"
#include "Socket.h"
#include "Acceptor.h"
#include "src/base/Logging.h"

#include <stdio.h>

TcpServer::TcpServer(EventLoop *loop,
                     const InetAddress &listenAddr,
                     const std::string &nameArg,
                     Option option)
    : loop_(CheckLoopNotNull(loop)),
      ipPort_(listenAddr.toIpPort()),
      name_(nameArg),
      acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
      threadPool_(new EventLoopThreadPool(loop, name_)),
      connectionCallback_(),
      messageCallback_(),
      started_(0),
      nextConnId_(1)
{
    acceptor_->setNewConnectionCallback([this](int sockfd, const InetAddress &peerAddr)
                                        { this->newConnection(sockfd, peerAddr); });
}

TcpServer::~TcpServer()
{
    loop_->assertInLoopThread();
    LOG_TRACE << "TcpServer::~TcpServer [" << name_ << "] destructing";

    for (auto &item : connections_)
    {
        TcpConnectionPtr conn(item.second);
        item.second.reset(); // item.second=nullptr,��ԭʼ������ָ�븴λ ��ջ�ռ��TcpConnectionPtr connָ��ö��� ��conn������������ �����ͷ�����ָ��ָ��Ķ���
        // ��������
        conn->getLoop()->runInLoop(
            std::bind(&TcpConnection::connectDestroyed, conn));
    }
}

// ���õײ�subloop�ĸ���
void TcpServer::setThreadNum(int numThreads)
{
    assert(0 <= numThreads);
    threadPool_->setThreadNum(numThreads);
}

// ��������������,�����̳߳أ�����Acceptor::listen
void TcpServer::start()
{
    if (started_++ == 0) // ��ֹһ��TcpServer����start���
    {
        threadPool_->start(threadInitCallback_); // �����ײ��loop�̳߳�
        assert(!acceptor_->listening());
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

// ��һ�����û����ӣ�acceptor��ִ������ص�����������mainLoop���յ�����������(acceptChannel_���ж��¼�����)ͨ���ص���ѯ�ַ���subLoopȥ����
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    loop_->assertInLoopThread();
    // ��ѯ�㷨 ѡ��һ��subLoop ������connfd��Ӧ��channel------------------
    EventLoop *ioLoop = threadPool_->getNextLoop();
    char buf[64] = {0};
    snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_; // ����û������Ϊԭ��������Ϊ��ֻ��mainloop��ִ�� ���漰�̰߳�ȫ����
    std::string connName = name_ + buf;
    LOG_INFO << "TcpServer::newConnection [" << name_
             << "] - new connection [" << connName
             << "] from " << peerAddr.toIpPort();
    // ͨ��sockfd��ȡ��󶨵ı�����ip��ַ�Ͷ˿���Ϣ
    sockaddr_in local;
    ::memset(&local, 0, sizeof(local));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(local));
    if (::getsockname(sockfd, reinterpret_cast<sockaddr *>(&local), &addrlen) < 0)
    {
        LOG_SYSERR << "sockets::getLocalAddr";
    }
    InetAddress localAddr(local);
    //����TcpConnection����----------------------------
    TcpConnectionPtr conn(std::make_shared<TcpConnection>(ioLoop,connName,sockfd,localAddr,peerAddr));
    connections_[connName] = conn;
    // ����Ļص������û����ø�TcpServer => TcpConnection�ģ�����Channel�󶨵�����TcpConnection���õ��ĸ���handleRead,handleWrite... ������Ļص�����handlexxx������
    conn->setConnectionCallback(connectionCallback_);
    conn->setMessageCallback(messageCallback_);
    conn->setWriteCompleteCallback(writeCompleteCallback_);
    // ��������ιر����ӵĻص�
    conn->setCloseCallback([this](const TcpConnectionPtr &con)
                           { this->removeConnection(con); });
    ioLoop->runInLoop(
        std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->runInLoop([this,con=std::move(conn)]()
                     { this->removeConnectionInLoop(con); });
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    loop_->assertInLoopThread();
    LOG_INFO << "TcpServer::removeConnectionInLoop [" << name_
             << "] - connection " << conn->name();
    connections_.erase(conn->name());
    EventLoop *ioLoop = conn->getLoop();
    ioLoop->queueInLoop(
        std::bind(&TcpConnection::connectDestroyed, conn));
}