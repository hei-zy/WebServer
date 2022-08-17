#include"Buffer.h"

#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>

const char Buffer::kCRLF[] = "\r\n";

/**
 * ��fd�϶�ȡ���� Poller������LTģʽ
 * Buffer���������д�С�ģ� ���Ǵ�fd�϶�ȡ���ݵ�ʱ�� ȴ��֪��tcp���ݵ����մ�С
 *
 * @description: ��socket�����������ķ�����ʹ��readv�ȶ���buffer_��
 * Buffer_�ռ������������뵽ջ��65536���ֽڴ�С�Ŀռ䣬Ȼ����append��
 * ��ʽ׷����buffer_���ȿ����˱���ϵͳ���ô����������ֲ�Ӱ�����ݵĽ��ա�
 **/
ssize_t Buffer::readFd(int fd, int *saveErrno)
{
    // ջ����ռ䣬���ڴ��׽���������ʱ����buffer_��ʱ������ʱ�ݴ����ݣ���buffer_���·����㹻�ռ���ڰ����ݽ�����buffer_��
    char extrabuf[65536] = {0}; // ջ���ڴ�ռ� 65536/1024 = 64KB
    /*
    struct iovec {
        ptr_t iov_base; // �ڴ���ʼ��ַ
        size_t iov_len; // �ڴ泤��
    };
    */
    // ʹ��iovec�������������Ļ�����
    struct iovec vec[2];
    const size_t writable = writableBytes(); // ����Buffer�ײ㻺����ʣ��Ŀ�д�ռ��С ��һ������ȫ�洢��fd����������

    // ��һ�黺������ָ���д�ռ�
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;
    // �ڶ��黺������ָ��ջ�ռ�
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);

    // when there is enough space in this buffer, don't read into extrabuf.
    // when extrabuf is used, we read 128k-1 bytes at most.
    // ����֮����˵���128k-1�ֽڣ�����Ϊ��writableΪ64k-1����ô��Ҫ���������� ��һ��64k-1 �ڶ���64k ��������128k-1
    // �����һ��������>=64k �Ǿ�ֻ����һ�������� ����ʹ��ջ�ռ�extrabuf[65536]������
    const int iovcnt = (writable < sizeof(extrabuf)) ? 2 : 1;
    const ssize_t n = ::readv(fd, vec, iovcnt);

    if (n < 0)
    {
        *saveErrno = errno;
    }
    else if (static_cast<size_t>(n) <= writable) // Buffer�Ŀ�д�������Ѿ����洢��������������
    {
        writerIndex_ += n;
    }
    else // extrabuf����Ҳд����n-writable���ȵ�����
    {
        writerIndex_ = buffer_.size();
        append(extrabuf, n - writable); // ��buffer_���� ����extrabuf�洢����һ��������׷����buffer_
    }
    return n;
}