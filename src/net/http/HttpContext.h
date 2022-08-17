#pragma once

#include"HttpRequest.h"

class Buffer;

class HttpContext
{
public:
    enum HttpRequestParseState
    {
        kExpectRequestLine,
        kExpectHeaders,
        kExpectBody,
        kGotAll,
    };

    HttpContext()
        : state_(kExpectRequestLine) {}

    //解析请求内容
    bool parseRequest(Buffer *buf, Timestamp receiveTime);

    bool gotAll() const
    {
        return state_ == kGotAll;
    }

    void reset()
    {
        state_ = kExpectRequestLine;
        HttpRequest().swap(request_);
    }

    const HttpRequest &request() const
    {
        return request_;
    }

    HttpRequest &request()
    {
        return request_;
    }

private:
    //处理请求行
    bool processRequestLine(const char *begin, const char *end);

    HttpRequestParseState state_;   //http请求解析状态
    HttpRequest request_;   //存放报文首部信息----请求行，首部字段
};