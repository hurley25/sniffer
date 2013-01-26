// =====================================================================================
// 
//       Filename:  mainwindow.h
//
//    Description:  主窗口的类声明头文件
//
//        Version:  1.0
//        Created:  2013年01月20日 17时02分49秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

#include "capturethread.h"

// 使用到的类的前置声明 P.S.在头文件里包含另一个大的头文件不是什么好的风格
class QAction;
class QLabel;
class QSplitter;
class QTextEdit;
class QTreeView;
class ListTreeView;
class QStandardItemModel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	friend class CaptureThread;

public:
	MainWindow();
	~MainWindow();

	void sleep(unsigned int msec);	// 延时函数

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void newFile();
    void open();
    void save();
    void print();
	
	void chooseDev();
	void begin();
	void end();
	void findQQ();
	void filter();
	void set();

	void about();

private:
	void createMainWeiget();		// 创建主窗口
	void createActions();			// 创建动作
	void createMenus();				// 创建主菜单
	void createToolBars();			// 创建工具栏
	void createStatusBar();			// 创建状态栏
	
	void readSettings();			// 读取配置文件
	void writeSettings();			// 写入配置文件

	bool isToContinue();			// 询问是否继续

	bool loadFile(const QString &fileName);			// 载入捕获文件
	bool saveFile(const QString &fileName);			// 保存捕获文件
	void setCurrentFile(const QString &fileName);	// 设置当前打开文件

	CaptureThread *captureThread;	// 数据捕获线程
	bool bCaptureStart;				// 是否开始捕获

	Sniffer *sniffer;				// 数据捕获类

	QString curFile;				// 当前打开文件

	QSplitter *rightSplitter;		// 右边的切分窗口
	QSplitter *mainSplitter;		// 总体的切分窗口

	ListTreeView *mainTreeView;		// 捕获的数据包列表
	QTreeView *explainTreeView;		// 捕获数据的解析

	QTextEdit *originalEdit;		// 捕获的原始数据包

	QLabel *statusLabel;			// 状态栏文本					
	
	QMenu *fileMenu;				// 主菜单-文件子菜单指针
	QMenu *toolsMenu;				// 主菜单-工具子菜单指针
	QMenu *optionsMenu;				// 主菜单-选项子菜单指针
	QMenu *helpMenu;				// 主菜单-帮助子菜单指针

	QToolBar *fileToolBar;			// 文件相关工具栏指针
	QToolBar *workToolBar;			// 捕获相关工具栏指针
	QToolBar *setToolBar;			// 设置相关工具栏指针
	QToolBar *infoToolBar;			// 帮助相关工具栏指针

	QAction *newAction;				// 创建一个新的捕获（清空历史）
	QAction *openAction;			// 打开历史的一个捕获记录
	QAction *saveAction;			// 保存本次捕获信息到文件
	QAction *printAction;			// 打印当前捕获的数据
	QAction *exitAction;			// 退出程序

	QAction *chooseDevAction;		// 选择打开的网卡
	QAction *beginAction;			// 开始捕获
	QAction *endAction;				// 停止捕获
	QAction *findQQAction;			// 捕获QQ信息
	QAction *filterAction;			// 设置过滤器
	QAction *setAction;				// 全局设置

	QAction *aboutAction;			// 关本于程序
	QAction *aboutQtAction;			// 关于Qt
};

#endif // MAINWINDOW_H_
