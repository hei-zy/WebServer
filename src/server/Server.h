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
    //由 请求报文req 生成相应的 响应报文resp
    void onRequest(const HttpRequest &req, HttpResponse *resp);

    //异步写日志
    void asyncOutput(const char *msg, int len);

    Config config_;
    AsyncLogging asyncLog_;
    HttpServer httpserver_;
};
