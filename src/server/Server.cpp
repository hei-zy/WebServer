#include "Server.h"
#include "src/net/InetAddress.h"
#include "src/net/http/HttpRequest.h"
#include "src/net/http/HttpResponse.h"

#include <iostream>
#include <unordered_map>
#include <string.h>

const char logpath[] = "./Log/serverlog";  //��־���·��
const off_t kRollSize = 500 * 1000 * 1000;  //�첽��־��������С

Server::Server(EventLoop *loop,
               const string &name,
               Config config)
    : config_(config),
      asyncLog_(::basename(logpath), kRollSize),
      httpserver_(loop, InetAddress(config.port()), "zy")
{
  httpserver_.setHttpCallback([this](const HttpRequest &req, HttpResponse *resp)
                              { this->onRequest(req, resp); });
  httpserver_.setThreadNum(config_.thread_num());
  //������־����ص�����
  Logger::setOutput([this](const char *msg, int len)
                    { this->asyncOutput(msg, len); });
  Logger::setLogLevel(Logger::WARN);  //������־�������
}

void Server::start()
{
  asyncLog_.start(); //�����첽��־
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

void Server::asyncOutput(const char *msg, int len)
{
  size_t n = fwrite(msg, 1, len, stdout);
  (void)n;
  asyncLog_.append(msg, len);  //д���첽��־������
}