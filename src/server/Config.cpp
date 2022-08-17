#include "Config.h"

#include<getopt.h>
#include<stdlib.h>

Config::Config(uint16_t port, int thread_num)
    : port_(port), thread_num_(thread_num) {}

Config::~Config() = default;

void Config::parse_arg(int argc, char *argv[])
{
    int opt;
    const char *str = "p:t:";
    while ((opt = ::getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'p':
        {
            port_ = static_cast<uint16_t>(atoi(optarg));
            break;
        }
        case 't':
        {
            thread_num_ = atoi(optarg);
            break;
        }
        default:
            break;
        }
    }
}