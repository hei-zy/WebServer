#include<iostream>
#include"server/Server.h"


//-p �˿ں� -t �߳���
int main(int argc, char**argv) {
    Config config;
    config.parse_arg(argc,argv);

    EventLoop loop;
    Server server(&loop,"zy",config);
    server.start();
    loop.loop();

    return 0;
}