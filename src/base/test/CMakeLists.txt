cmake_minimum_required(VERSION 3.16)
# project (LogTest)

add_executable(LogTest LogTest.cpp)
target_link_libraries(LogTest webserver_base)

add_executable(Thread_test Thread_test.cpp)
target_link_libraries(Thread_test webserver_base)