
#ifndef LISTTREEVIEW_H_
#define LISTTREEVIEW_H_

#include <QTableView>
#include <QTreeView>

class QStandardItemModel;
class QModelIndex;
class QString;

class CapTableView : public QTreeView
{
	Q_OBJECT

public:
    CapTableView();
    ~CapTableView();

    void resetInfo();
    int haveData();
	void addOneCaptureItem(QString strNum, QString strTime, QString strSIP, 
								QString strDIP, QString strProto, QString strLength);

	void getOrderNumber(QModelIndex &index, QString &strNumber);

private:
    QStandardItemModel *dataModel;
    int lastPosition;
};

#endif // LISTTREEVIEW_H_
