// =====================================================================================
// 
//       Filename:  choosedevdialog.h
//
//    Description:  选择适配器对话框类声明文件
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

#ifndef CHOOSEDEVDIALOG_H
#define CHOOSEDEVDIALOG_H

#include <QDialog>

#include "ui_choosedevdialog.h"

class ChooseDevDialog : public QDialog, public Ui::ChooseDevDialog
{
	Q_OBJECT

public:
    ChooseDevDialog(QWidget *parent = 0);

    void addNetNevInfo();

private slots:
	void helpDialog();


};

#endif	// CHOOSEDEVDIALOG_H