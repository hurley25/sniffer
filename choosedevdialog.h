
#ifndef CHOOSEDEVDIALOG_H
#define CHOOSEDEVDIALOG_H

#include <QDialog>

#include <vector>

#include "ui_choosedevdialog.h"

class  Sniffer;
struct SettingInfo;

class ChooseDevDialog : public QDialog, public Ui::ChooseDevDialog
{
	Q_OBJECT

public:
	ChooseDevDialog(QWidget *parent = 0);
	ChooseDevDialog(Sniffer *sni, QWidget *parent = 0);

	void GetUserSet(SettingInfo *settingInfo);

	void addNetDevInfo();

    int 		openDevNumber;
    bool 		isPromiscuous;
    bool 		isAutoBegin;
    int	 		pakectByteLimit;
	std::string	filterString;

private slots:
	void helpDialog();
	void setChoose(QListWidgetItem *changedElem);
	void setPromiscuousFlag(int flag);
	void setAutoBeginFlag(int flag);
	void setDataLimitValue(int iValue);
	void setFilterString(int index);

private:
	std::vector<QListWidgetItem *> devItemVector;
	Sniffer 	*sniffer;
};

#endif	// CHOOSEDEVDIALOG_H
