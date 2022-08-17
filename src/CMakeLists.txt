cmake_minimum_required(VERSION 3.16)


project (server)

set(SRCS
    main.cpp
    server/Server.cpp
    server/Config.cpp
  )


add_executable(server ${SRCS})
target_link_libraries(server webserver_http)