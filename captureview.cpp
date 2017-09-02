
#include <QtGui>

#include "captureview.h"

CapTableView::CapTableView()
{
    lastPosition = 0;

    dataModel = new QStandardItemModel;

    dataModel->setColumnCount(6);
    dataModel->setHeaderData(0, Qt::Horizontal, tr("No."));
    dataModel->setHeaderData(1, Qt::Horizontal, tr("Time"));
    dataModel->setHeaderData(2, Qt::Horizontal, tr("Source"));
    dataModel->setHeaderData(3, Qt::Horizontal, tr("Destination"));
    dataModel->setHeaderData(4, Qt::Horizontal, tr("Protocol"));
    dataModel->setHeaderData(5, Qt::Horizontal, tr("Length"));

    this->setAutoFillBackground(true);
    this->setSortingEnabled(true);
    this->setModel(dataModel);
}

CapTableView::~CapTableView()
{

}

void CapTableView::resetInfo()
{
    dataModel->clear();
    lastPosition = 0;

    dataModel->setColumnCount(6);
    dataModel->setHeaderData(0, Qt::Horizontal, tr("No."));
    dataModel->setHeaderData(1, Qt::Horizontal, tr("Time"));
    dataModel->setHeaderData(2, Qt::Horizontal, tr("Source"));
    qDebug() << "shit" << endl;
    dataModel->setHeaderData(3, Qt::Horizontal, tr("Destination"));
    qDebug() << "shit" << endl;
    dataModel->setHeaderData(4, Qt::Horizontal, tr("Protocol"));
    dataModel->setHeaderData(5, Qt::Horizontal, tr("Length"));
}

void CapTableView::addOneCaptureItem(QString strNum, QString strTime, QString strSIP,
										QString strDIP, QString strProto, QString strLength)
{
	QStandardItem *item;

    item = new QStandardItem(strNum);
    dataModel->setItem(lastPosition, 0, item);
    item = new QStandardItem(strTime);
    dataModel->setItem(lastPosition, 1, item);
    item = new QStandardItem(strSIP);
    dataModel->setItem(lastPosition, 2, item);
    item = new QStandardItem(strDIP);
    dataModel->setItem(lastPosition, 3, item);
    item = new QStandardItem(strProto);
    dataModel->setItem(lastPosition, 4, item);
    item = new QStandardItem(strLength);
    dataModel->setItem(lastPosition, 5, item);
    static unsigned short mod = 64;
    if(lastPosition == 0 || mod < 2)
        mod = 1;
    if(lastPosition % mod == 0)
    {
        for(int i = 0; i < 6; i++)
            this->resizeColumnToContents(i);
        mod <<= 2;
    }
    lastPosition++;
}

void CapTableView::getOrderNumber(QModelIndex &index, QString &strNumber)
{
    strNumber = dataModel->data(index, 0).toString();
}

int CapTableView::haveData()
{
   return this->dataModel->rowCount();
}
