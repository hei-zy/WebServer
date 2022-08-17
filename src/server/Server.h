#pragma once

#include"src/net/http/HttpServer.h"
#include"Config.h"
#include"src/net/EventLoop.h"

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

    Config config_;
    HttpServer httpserver_;
};

