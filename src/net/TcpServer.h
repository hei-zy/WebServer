#pragma once

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>
#include<map>

#include"TcpConnection.h"
#include"Callbacks.h"
#include"src/base/noncopyable.h"
#include"InetAddress.h"

class Acceptor;
class EventLoop;
class EventLoopThreadPool;

class TcpServer:noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;
    enum Option
    {
        kNoReusePort,
        kReusePort,
    };

    TcpServer(EventLoop *loop,
              const InetAddress &listenAddr,
              const std::string &nameArg,
              Option option = kNoReusePort);
    ~TcpServer();

    // ��������������
    void start();

    // ���õײ�subloop�ĸ���
    void setThreadNum(int numThreads);

    //�����¼��ص�
    void setThreadInitCallback(const ThreadInitCallback &cb) { threadInitCallback_ = cb; }
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }

    const std::string &ipPort() const { return ipPort_; }
    const std::string &name() const { return name_; }
    EventLoop *getLoop() const { return loop_; }

private:
    //runInLoop��֤�̰߳�ȫ
    void newConnection(int sockfd, const InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

    using ConnectionMap = std::map<std::string, TcpConnectionPtr>;

    EventLoop *loop_; // baseloop mainLoop,��acceptor_���ڵ�loop
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_; // ������mainloop ������Ǽ����������¼�
    std::shared_ptr<EventLoopThreadPool> threadPool_; // one loop per thread
    ConnectionCallback connectionCallback_;       //��������ʱ�Ļص�
    MessageCallback messageCallback_;             // �ж�д�¼�����ʱ�Ļص�
    WriteCompleteCallback writeCompleteCallback_; // ��Ϣ������ɺ�Ļص�
    ThreadInitCallback threadInitCallback_; // loop�̳߳�ʼ���Ļص�
    std::atomic_int started_;       //server��start()��������ֹ�������
    int nextConnId_;
    ConnectionMap connections_; // �������е�����
};