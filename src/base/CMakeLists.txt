# cmake_minimum_required(VERSION 3.16)
set(LIB_SRC
    AsyncLogging.cpp
    CountDownLatch.cpp
    FileUtil.cpp
    LogFile.cpp
    Logging.cpp
    LogStream.cpp
    Thread.cpp
    CurrentThread.cpp
    Timestamp.cpp
)

add_library(webserver_base ${LIB_SRC})
target_link_libraries(webserver_base pthread rt)

# set_target_properties(libserver_base PROPERTIES OUTPUT_NAME "server_base")

install(TARGETS webserver_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/src/base)

# add_subdirectory(test)