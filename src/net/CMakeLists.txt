cmake_minimum_required(VERSION 3.16)

set(net_SRCS
  Acceptor.cpp
  Buffer.cpp
  Channel.cpp
  EventLoop.cpp
  EventLoopThread.cpp
  EventLoopThreadPool.cpp
  InetAddress.cpp
  Poller.cpp
  poller/DefaultPoller.cpp
  poller/EPollPoller.cpp
  Socket.cpp
  TcpConnection.cpp
  TcpServer.cpp
  Timer.cpp
  TimerQueue.cpp
  )

include_directories(../../src)
include_directories(../../)



add_library(webserver_net ${net_SRCS})
target_link_libraries(webserver_net webserver_base)



# install(TARGETS webserver_net DESTINATION lib)

# set(HEADERS
#   Buffer.h
#   Callbacks.h
#   Channel.h
#   EventLoop.h
#   EventLoopThread.h
#   EventLoopThreadPool.h
#   InetAddress.h
#   TcpConnection.h
#   TcpServer.h
#   TimerId.h
#   )
# install(FILES ${HEADERS} DESTINATION include/src/net)

add_subdirectory(http)

add_subdirectory(tests)