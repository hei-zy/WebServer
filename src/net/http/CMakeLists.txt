set(http_SRCS
  HttpServer.cpp
  HttpResponse.cpp
  HttpContext.cpp
  )

add_library(webserver_http ${http_SRCS})

target_link_libraries(webserver_http webserver_net)

install(TARGETS webserver_http DESTINATION lib)
set(HEADERS
  HttpContext.h
  HttpRequest.h
  HttpResponse.h
  HttpServer.h
  )
install(FILES ${HEADERS} DESTINATION include/src/net/http)



add_subdirectory(tests)
