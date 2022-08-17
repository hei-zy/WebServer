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

    // 开启服务器监听
    void start();

    // 设置底层subloop的个数
    void setThreadNum(int numThreads);

    //设置事件回调
    void setThreadInitCallback(const ThreadInitCallback &cb) { threadInitCallback_ = cb; }
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }

    const std::string &ipPort() const { return ipPort_; }
    const std::string &name() const { return name_; }
    EventLoop *getLoop() const { return loop_; }

private:
    //runInLoop保证线程安全
    void newConnection(int sockfd, const InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

    using ConnectionMap = std::map<std::string, TcpConnectionPtr>;

    EventLoop *loop_; // baseloop mainLoop,即acceptor_所在的loop
    const std::string ipPort_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_; // 运行在mainloop 任务就是监听新连接事件
    std::shared_ptr<EventLoopThreadPool> threadPool_; // one loop per thread
    ConnectionCallback connectionCallback_;       //有新连接时的回调
    MessageCallback messageCallback_;             // 有读写事件发生时的回调
    WriteCompleteCallback writeCompleteCallback_; // 消息发送完成后的回调
    ThreadInitCallback threadInitCallback_; // loop线程初始化的回调
    std::atomic_int started_;       //server被start()次数，防止多次启动
    int nextConnId_;
    ConnectionMap connections_; // 保存所有的连接
};