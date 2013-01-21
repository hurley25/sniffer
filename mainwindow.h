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

class QAction;
class QLabel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

	void sleep(unsigned int msec);	// 延时函数

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void about();

private:
	void createActions();			// 创建动作
	void createMenus();				// 创建主菜单
	void createContextMenu();		// 创建程序界面菜单
	void createToolBars();			// 创建工具栏
	void createStatusBar();			// 创建状态栏

	bool isToContinue();			// 询问是否继续

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

	QAction *beginAction;			// 开始捕获
	QAction *endAction;				// 停止捕获
	QAction *filterAction;			// 设置过滤器
	QAction *findQQAction;			// 捕获QQ信息
	QAction *setAction;				// 全局设置

	QAction *aboutAction;			// 关本于程序
	QAction *aboutQtAction;			// 关于Qt
};

#endif // MAINWINDOW_H_
