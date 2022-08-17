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

    //������������
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
    //����������
    bool processRequestLine(const char *begin, const char *end);

    HttpRequestParseState state_;   //http�������״̬
    HttpRequest request_;   //��ű����ײ���Ϣ----�����У��ײ��ֶ�
};