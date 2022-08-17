cmake_minimum_required(VERSION 3.16)
project (echoserver_unittest)


add_executable(echoserver_unittest EchoServer_unittest.cpp)
target_link_libraries(echoserver_unittest webserver_net)

add_executable(EventLoop_unittest EventLoop_unittest.cpp)
target_link_libraries(EventLoop_unittest webserver_net)

add_executable(EventLoopThread_unittest EventLoopThread_unittest.cpp)
target_link_libraries(EventLoopThread_unittest webserver_net)

add_executable(EventLoopThreadPool_unittest EventLoopThreadPool_unittest.cpp)
target_link_libraries(EventLoopThreadPool_unittest webserver_net)