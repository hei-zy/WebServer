#pragma once

//��װAppendFile������ʵ���̰߳�ȫ��������һ������ʱˢ�»�����
#include <memory>
#include <mutex>
#include <string>

#include "noncopyable.h"

class AppendFile;

using std::string;
class LogFile : noncopyable
{
public:
    LogFile(const string &basename,
            off_t rollSize,
            bool threadSafe = true,
            int flushInterval = 3,
            int checkEveryN = 1024);
    ~LogFile();

    void append(const char* logline, int len);
    void flush();
    bool rollFile(); //�����ļ�
private:
    void append_unlocked(const char* logline, int len);

    static string getLogFileName(const string& basename, time_t* now);
private:
    const string basename_;     //�ļ���ǰ׺
    const off_t rollSize_;      //��������С
    const int flushInterval_;   //ˢ�»�������ʱ����
    const int checkEveryN_;     //����write��������

    int count_; //����write����

    std::unique_ptr<std::mutex> uniMutex_;
    time_t startOfPeriod_;
    time_t lastRoll_;
    time_t lastFlush_;
    std::unique_ptr<AppendFile> file_;

    const static int kRollPerSeconds_=60*60*24;
};