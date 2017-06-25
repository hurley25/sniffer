
#include "capturethread.h"
#include "captureview.h"
#include "sniffer.h"
#include <QDebug>

CaptureThread::CaptureThread():mainTree(nullptr),sniffer(nullptr){}

CaptureThread::CaptureThread(CapTableView *pTree, QString tmpFileName)
    :mainTree(pTree),sniffer(Sniffer::get_sniffer()),tmpFile(tmpFileName){}

void CaptureThread::reset(CapTableView *pTree, QString tmpFileName)
{
    stop();
    mainTree = pTree;
    sniffer = Sniffer::get_sniffer();
    tmpFile =  tmpFileName;
}

void CaptureThread::run()
{
    int res, num = 0;
    if (!tmpFile.isEmpty()) {
        sniffer->openDumpFile((const char *)tmpFile.toLocal8Bit());
    }

    sniffer->reset(); // 清理遗留数据

    while ((res = sniffer->captureOnce()) >= 0)
    {
        if (res == 0)
            continue;
        if (num > 65535)
            break;
        sniffer->deal_packet(mainTree, num++);
    }
}

void CaptureThread::stop()
{
    if(this->isRunning())
        this->terminate();
    while(!this->isFinished())
    {
        this->terminate();
//        this->msleep(50);
//        qDebug() << "Still Running" << endl;
    }
}
