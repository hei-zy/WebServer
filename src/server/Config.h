#pragma once

#include<stdint.h>

class Config
{
public:
    Config(uint16_t port = 8000, int thread_num = 1);
    ~Config();

    uint16_t port() const { return port_; }

    int thread_num() const {return thread_num_;}

    void parse_arg(int argc, char *argv[]);

private:
    //�˿ں�
    uint16_t port_;
    //�̳߳��ڵ��߳�����
    int thread_num_;
};

