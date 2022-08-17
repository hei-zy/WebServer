#pragma once

#include "src/base/noncopyable.h"
#include "InetAddress.h"
#include "Callbacks.h"
#include "src/base/Timestamp.h"
#include "Buffer.h"
#include "src/base/Logging.h"

#include <memory>
#include <string>
#include <atomic>
#include<any>

class Channel;
class EventLoop;
class Socket;

/**
 * TcpServer => Acceptor => ��һ�����û����ӣ�ͨ��accept�����õ�connfd
 * => TcpConnection���ûص� => ���õ�Channel => Poller => Channel�ص�
 **/
class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop *loop,
                  const std::string &nameArg,
                  int sockfd,
                  const InetAddress &localAddr,
                  const InetAddress &peerAddr);
    ~TcpConnection();

    EventLoop *getLoop() const { return loop_; }
    const std::string &name() const { return name_; }
    const InetAddress &localAddress() const { return localAddr_; }
    const InetAddress &peerAddress() const { return peerAddr_; }

    bool connected() const { return state_ == kConnected; }

    // ��������
    void send(const std::string &buf);
    void send(Buffer *message);
    // �ر�����---shutdownWrite()�ر�д��
    void shutdown();

    void setTcpNoDelay(bool on);

    void setContext(const std::any &context)
    {
        context_ = context;
    }

    std::any *getMutableContext()
    {
        return &context_;
    }

    void setConnectionCallback(const ConnectionCallback &cb)
    {
        connectionCallback_ = cb;
    }
    void setMessageCallback(const MessageCallback &cb)
    {
        messageCallback_ = cb;
    }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb)
    {
        writeCompleteCallback_ = cb;
    }
    void setCloseCallback(const CloseCallback &cb)
    {
        closeCallback_ = cb;
    }
    void setHighWaterMarkCallback(const HighWaterMarkCallback &cb, size_t highWaterMark)
    {
        highWaterMarkCallback_ = cb;
        highWaterMark_ = highWaterMark;
    }

    // �����ӽ���ʱ��TcpServerͨ��runInLoop()��loop��ע��
    void connectEstablished();
    // �������٣�TcpServerͨ��runInLoop()��loop��ע��
    void connectDestroyed();

private:
    enum StateE
    {
        kDisconnected, // �Ѿ��Ͽ�����
        kConnecting,   // ��������
        kConnected,    // ������
        kDisconnecting // ���ڶϿ�����
    };
    void setState(StateE state) { state_ = state; }
    const char *stateToString() const;

    void handleRead(Timestamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void *data, size_t len);
    void shutdownInLoop();

    EventLoop *loop_; // ������baseloop����subloop��TcpServer�д������߳������� ��Ϊ��Reactor ��loop_ָ��subloop ��Ϊ��Reactor ��loop_ָ��baseloop
    const std::string name_;
    std::atomic_int state_;
    bool reading_;

    // Socket Channel �����Acceptor����    Acceptor => mainloop    TcpConnection => subloop
    std::unique_ptr<Socket> socket_;   //����������TcpConnection����
    std::unique_ptr<Channel> channel_; //����������TcpConnection����

    const InetAddress localAddr_;
    const InetAddress peerAddr_;

    // runInLoop() ��Щ�ص�TcpServerҲ�� �û�ͨ��д��TcpServerע�� TcpServer�ٽ�ע��Ļص����ݸ�TcpConnection TcpConnection�ٽ��ص�ע�ᵽChannel��
    ConnectionCallback connectionCallback_;       // ��������ʱ�Ļص�
    MessageCallback messageCallback_;             // �ж�д��Ϣʱ�Ļص�
    WriteCompleteCallback writeCompleteCallback_; // ��Ϣ��������Ժ�Ļص�
    CloseCallback closeCallback_;                 // �ر����ӵĻص�
    HighWaterMarkCallback highWaterMarkCallback_; //����highWaterMark_�Ļص�

    size_t highWaterMark_; //���ͻ��������ޣ�������ֵ������Ҫ��channelע��д�¼�

    // ���ݻ�����
    Buffer inputBuffer_;  // �������ݵĻ�����
    Buffer outputBuffer_; // �������ݵĻ����� �û�send��outputBuffer_��

    std::any context_;
};

const char *strerror_tl(int savedErrno);

EventLoop *CheckLoopNotNull(EventLoop *loop);