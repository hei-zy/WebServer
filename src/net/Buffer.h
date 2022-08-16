#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <stddef.h>
#include<string.h>
#include <sys/types.h>

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initalSize = kInitialSize)
        : buffer_(kCheapPrepend + initalSize), readerIndex_(kCheapPrepend), writerIndex_(kCheapPrepend)
    {
    }

    size_t readableBytes() const { return writerIndex_ - readerIndex_; }
    size_t writableBytes() const { return buffer_.size() - writerIndex_; }
    size_t prependableBytes() const { return readerIndex_; }

    // ���ػ������пɶ����ݵ���ʼ��ַ
    const char *peek() const { return begin() + readerIndex_; }

    void retrieve(size_t len)
    {
        if (len < readableBytes())
        {
            readerIndex_ += len; // ˵��Ӧ��ֻ��ȡ�˿ɶ����������ݵ�һ���֣�����len���� ��ʣ��readerIndex+=len��writerIndex_������δ��
        }
        else // len == readableBytes()
        {
            retrieveAll();
        }
    }

    //�ռ����
    void retrieveAll()
    {
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    // ��onMessage�����ϱ���Buffer���� ת��string���͵����ݷ���
    std::string retrieveAllAsString() { return retrieveAsString(readableBytes()); }
    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        retrieve(len); // ����һ��ѻ������пɶ��������Ѿ���ȡ���� ����϶�Ҫ�Ի��������и�λ����
        return result;
    }

    // buffer_.size - writerIndex_
    void ensureWritableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len); // ����
        }
    }

    // ��[data, data+len]�ڴ��ϵ�������ӵ�writable����������
    void append(const char *data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        writerIndex_ += len;
    }
    char *beginWrite() { return begin() + writerIndex_; }
    const char *beginWrite() const { return begin() + writerIndex_; }

    // ��fd�϶�ȡ����
    ssize_t readFd(int fd, int *saveErrno);

private:
    // vector�ײ�������Ԫ�صĵ�ַ Ҳ�����������ʼ��ַ
    char *begin() { return &*buffer_.begin(); }
    const char *begin() const { return &*buffer_.begin(); }

    void makeSpace(size_t len)
    {
        /**
         * | kCheapPrepend |xxx| reader | writer |                     // xxx��ʾreader���Ѷ��Ĳ���
         * | kCheapPrepend | reader ��          len          |
         **/
        if (writableBytes() + prependableBytes() < len + kCheapPrepend) // Ҳ����˵ len > xxx + writer�Ĳ���
        {
            buffer_.resize(writerIndex_ + len);
        }
        else // ����˵�� len <= xxx + writer ��reader�ᵽ��xxx��ʼ ʹ��xxx������һ�������ռ�
        {
            size_t readable = readableBytes(); // readable = reader�ĳ���
            std::copy(begin() + readerIndex_,
                      begin() + writerIndex_, // ����һ�������ݿ�����begin+kCheapPrepend��ʼ��
                      begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};