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
    //��TcpServer->conn��ע��������ӻص������Ӵ���ʱ���ã�,�ڸ������ϴ���һ��HttpContext����
    void onConnection(const TcpConnectionPtr &conn);
    //��TcpServer->conn��ע�������Ϣ�ص�(��handlread�е��ã����ɶ��¼��ص�����)���������http���ģ�������onRequest����http����
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp receiveTime);
    //����http���󣬲�����httpCallback_��дhttp��Ӧ���ģ�����Ӧ����д��conn->outputBuffer_�������͸��ͻ���
    void onRequest(const TcpConnectionPtr &, const HttpRequest &);

    TcpServer server_;
    HttpCallback httpCallback_;
};
