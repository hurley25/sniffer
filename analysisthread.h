#ifndef ANALYSISTHREAD_H
#define ANALYSISTHREAD_H
#include<QThread>

class Sniffer;
class AnalysisThread : public QThread
{
    Q_OBJECT
public:
    AnalysisThread();
    void stop();
    ~AnalysisThread();
protected:
    void run();
private:
    Sniffer * sniffer;
};

#endif // ANALYSISTHREAD_H
