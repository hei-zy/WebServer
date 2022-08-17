#include "Server.h"
#include "src/net/InetAddress.h"
#include "src/net/http/HttpRequest.h"
#include "src/net/http/HttpResponse.h"

#include <iostream>
#include <unordered_map>

Server::Server(EventLoop *loop,
               const string &name,
               Config config)
    : config_(config),
      httpserver_(loop, InetAddress(config.port()), "zy")
{
  httpserver_.setHttpCallback([this](const HttpRequest &req, HttpResponse *resp)
                              { this->onRequest(req, resp); });
  httpserver_.setThreadNum(config_.thread_num());
}

void Server::start()
{
  httpserver_.start();
}

void Server::onRequest(const HttpRequest &req, HttpResponse *resp)
{
  std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;

  if (req.path() == "/")
  {
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setStatusMessage("OK");
    resp->setContentType("text/html");
    resp->addHeader("Server", "zy");
    string now = Timestamp::now().toString();
    resp->setBody("<html><head><title>This is title</title></head>"
                  "<body><h1>Hello</h1>Now is " +
                  now +
                  "</body></html>");
  }
  else
  {
    resp->setStatusCode(HttpResponse::k404NotFound);
    resp->setStatusMessage("Not Found");
    resp->setCloseConnection(true);
  }
}