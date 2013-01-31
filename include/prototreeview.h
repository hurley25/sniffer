// =====================================================================================
// 
//       Filename:  prototreeview.h
//
//    Description:  协议解析类的声明文件
//
//        Version:  1.0
//        Created:  2013年01月30日 23时08分10秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
//        Company:  Class 1107 of Computer Science and Technology
// 
// =====================================================================================

#ifndef PROTOTREEVIEW_H_
#define PROTOTREEVIEW_H_

#include <QTreeView>
#include <QString>

class QStandardItemModel;
class QByteArray;
struct SnifferData;

class ProtoTreeView : public QTreeView
{
	Q_OBJECT

public:
	ProtoTreeView();
	~ProtoTreeView();

	void rebuildInfo();
	void ShowTreeAnalyseInfo(SnifferData *snifferData);

private:
	QStandardItemModel *mainModel;
};

#endif	PROTOTREEVIEW_H_
