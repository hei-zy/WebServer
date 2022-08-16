#include "../TcpServer.h"
#include"../TcpConnection.h"

#include "../../base/Logging.h"
#include "../../base/Thread.h"
#include "../EventLoop.h"
#include "../InetAddress.h"

#include <utility>

#include <stdio.h>
#include <unistd.h>
#include<string>
#include <functional>


int numThreads = 0;

class EchoServer
{
public:
  EchoServer(EventLoop *loop, const InetAddress &listenAddr)
      : loop_(loop),
        server_(loop, listenAddr, "EchoServer")
  {
    server_.setConnectionCallback([this](const TcpConnectionPtr &conn)
                                  { this->onConnection(conn); });
    server_.setMessageCallback([this](const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
                               { this->onMessage(conn, buf, time); });
    server_.setThreadNum(numThreads);
  }

  void start()
  {
    server_.start();
  }
  // void stop();

private:
  void onConnection(const TcpConnectionPtr &conn)
  {
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
              << conn->localAddress().toIpPort() << " is "
              << (conn->connected() ? "UP" : "DOWN");

    conn->send("hello\n");
  }

  void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
  {
    std::string msg(buf->retrieveAllAsString());
    LOG_TRACE << conn->name() << " recv " << msg.size() << " bytes at " << time.toString();
    if (msg == "exit\n")
    {
      conn->send("bye\n");
      conn->shutdown();
    }
    if (msg == "quit\n")
    {
      loop_->quit();
    }
    conn->send(msg);
  }

  EventLoop *loop_;
  TcpServer server_;
};

int main(int argc, char *argv[])
{
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);
  if (argc > 1)
  {
    numThreads = atoi(argv[1]);
  }
  // bool ipv6 = argc > 2;
  EventLoop loop;
  InetAddress listenAddr(2000, false);
  EchoServer server(&loop, listenAddr);

  server.start();

  loop.loop();
}
