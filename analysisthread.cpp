#include<QDebug>

#include "analysisthread.h"
#include "sniffer.h"

AnalysisThread::AnalysisThread():sniffer(Sniffer::get_sniffer()){}

AnalysisThread::~AnalysisThread()
{

}

void AnalysisThread::stop()
{
    if(this->isRunning())
        this->terminate();
    this->msleep(50);
    while(!this->isFinished())
    {
        qDebug() << "Still Running" << endl;
    }
}

void AnalysisThread::run()
{

}
