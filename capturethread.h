
#ifndef CAPTURETHREAD_H_
#define CAPTURETHREAD_H_

#include <QThread>

class CapTableView;
class Sniffer;

class  CaptureThread : public QThread
{
	Q_OBJECT

public:
	CaptureThread();
    CaptureThread(CapTableView *pTree, QString tmpFileName = "");
    void reset(CapTableView *pTree, QString tmpFileName = "");
	void stop();

protected:
	void run();

private:
    CapTableView *mainTree;
    Sniffer *sniffer;
    QString tmpFile;
};

#endif	// CAPTURETHREAD_H_
