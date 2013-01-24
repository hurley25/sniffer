// =====================================================================================
// 
//       Filename:  capturethread.h
//
//    Description:  后台捕获数据的多线程类头文件
//
//        Version:  1.0
//        Created:  2013年01月24日 21时36分49秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================
#ifndef CAPTURETHREAD_H_
#define CAPTURETHREAD_H_

#include <QThread.h>

class ListTreeView;
class Sniffer;

class  CaptureThread : public QThread
{
	Q_OBJECT

public:
	CaptureThread();
	void stop();

	ListTreeView *mainTree;
	Sniffer *sniffer;

protected:
	void run();

private:
	volatile bool bStopped;
};

#endif	// CAPTURETHREAD_H_
