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

struct AnalyseProtoType
{
	QString strEthTitle;		// 数据链路层
	QString strDMac;
	QString strSMac;
	QString strType;

	QString strIPTitle;			// 网络层
	QString strVersion;
	QString strHeadLength;
	QString strServerType;
	QString strLength;
	QString strNextProto;
	QString strSIP;
	QString strDIP;

	QString strTranProto;		// 传输层
	QString strSPort;
	QString strDPort;

	QString strAppProto;		// 应用层
	QString strSendInfo;

	AnalyseProtoType()
	{
		strEthTitle = "数据链路层 Ethrmet II";
		strDMac = "目标MAC地址：";
		strSMac = "来源MAC地址：";
		strType = "以太网类型：";

		strIPTitle = "IP 协议";
		strVersion = "版本：";
		strHeadLength = "协议头长度：";
		strServerType = "服务类型：";
		strLength = "总长：";
		strNextProto = "高层协议类型：";
		strSIP = "来源IP地址：";
		strDIP = "目标IP地址：";

		strSPort = "来源端口号：";
		strDPort = "目标端口号：";
	}
};

class QStandardItemModel;
class QByteArray;

class ProtoTreeView : public QTreeView
{
	Q_OBJECT

public:
	ProtoTreeView();
	~ProtoTreeView();

	void rebuildInfo();
	void AnalyseProto(QByteArray *rawData);
	void ShowTreeAnalyseInfo();

private:
	QStandardItemModel *mainModel;
	AnalyseProtoType   *protoInfo;
};

#endif	PROTOTREEVIEW_H_
