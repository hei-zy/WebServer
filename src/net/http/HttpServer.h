#pragma once

#include"src/net/TcpServer.h"
#include"src/base/noncopyable.h"

#include<string>

class HttpRequest;
class HttpResponse;

using std::string;

class HttpServer : noncopyable
{
public:
    using HttpCallback = std::function<void(const HttpRequest &, HttpResponse *)>;

    HttpServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &name,
               TcpServer::Option option = TcpServer::kNoReusePort);

    EventLoop *getLoop() const { return server_.getLoop(); }

    void setHttpCallback(const HttpCallback &cb)
    {
        httpCallback_ = cb;
    }

    void setThreadNum(int numThreads)
    {
        server_.setThreadNum(numThreads);
    }

    void start();

private:
    //向TcpServer->conn中注册的新连接回调（连接创建时调用）,在该连接上创建一个HttpContext对象
    void onConnection(const TcpConnectionPtr &conn);
    //向TcpServer->conn中注册的有信息回调(在handlread中调用，即可读事件回调函数)，负责解析http报文，并调用onRequest处理http请求
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp receiveTime);
    //处理http请求，并调用httpCallback_填写http响应报文，后将响应报文写进conn->outputBuffer_，并发送给客户端
    void onRequest(const TcpConnectionPtr &, const HttpRequest &);

    TcpServer server_;
    HttpCallback httpCallback_;
};
