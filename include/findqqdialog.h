// =====================================================================================
// 
//       Filename:  findqqdialog.h
//
//    Description:  捕获QQ信息对话框类声明文件
//
//        Version:  1.0
//        Created:  2013年01月26日 21时01分49秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef FINDQQDIALOG_H_
#define FINDQQDIALOG_H_

#include <QDialog>

#include <string>
#include <map>

#include "ui_findqqdialog.h"

class FindQQThread;
class MainWindow;
class Sniffer;

class FindQQDialog : public QDialog, public Ui::FindQQDialog
{
	Q_OBJECT

public:
	FindQQDialog(QWidget *parent = 0);
	FindQQDialog(QWidget *parent, MainWindow *window, Sniffer *sni);

	void addOneFindInfo(const char *szFirstTime, const char *szLastTime, const char *szSIP,
									 const char *szDIP, const char *szQQ, const char *szSum);
	
	void changeOneInfoNum(const char *szLastTime, const char *szQQ, const char *szSum);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void beginFind();
	void endFind();
	void showHelpInfo();

private:
	FindQQThread  *findQQThread;
	MainWindow    *mainwindow;
	Sniffer 	  *sniffer;

	typedef std::map<std::string, QTreeWidgetItem *> ItemMaptype;
	ItemMaptype	  itemMap;
};

#endif	// FINDQQDIALOG_H_