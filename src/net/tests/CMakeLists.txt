cmake_minimum_required(VERSION 3.16)
project (echoserver_unittest)


add_executable(echoserver_unittest EchoServer_unittest.cpp)
target_link_libraries(echoserver_unittest webserver_net)