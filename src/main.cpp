#include<iostream>
#include"server/Server.h"


//-p 端口号 -t 线程数
int main(int argc, char**argv) {
    Config config;
    config.parse_arg(argc,argv);

    EventLoop loop;
    Server server(&loop,"zy",config);
    server.start();
    loop.loop();

    return 0;
}