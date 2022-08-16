#pragma once

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>


//��װsocket��ַ����
class InetAddress
{
public:
    explicit InetAddress(uint16_t port=0, bool loopbackOnly=false);

    InetAddress(uint16_t port, std::string ip);

    explicit InetAddress(const sockaddr_in& addr);

    //�������ֽ���ת��Ϊstring��int
    std::string toIp() const; // inet_ntop
    std::string toIpPort() const; // inet_ntop ntohs
    uint16_t toPort() const;      // ntohs

    const sockaddr_in *getSockAddr() const { return &addr_; }

    void setSockAddr(const sockaddr_in &addr) { addr_ = addr; }

private:
    sockaddr_in addr_;  //socket��ַ
};