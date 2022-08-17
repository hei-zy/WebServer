#pragma once

#include "src/net/http/HttpServer.h"
#include "Config.h"
#include "src/net/EventLoop.h"
#include "src/base/AsyncLogging.h"

#include <memory>

class HttpRequest;
class HttpResponse;

class Server
{
public:
    using HttpCallback = std::function<void(const HttpRequest &, HttpResponse *)>;

    Server(EventLoop *loop,
           const string &name,
           Config config);

    void start();

private:
    //�� ������req ������Ӧ�� ��Ӧ����resp
    void onRequest(const HttpRequest &req, HttpResponse *resp);

    //�첽д��־
    void asyncOutput(const char *msg, int len);

    Config config_;
    AsyncLogging asyncLog_;
    HttpServer httpserver_;
};
