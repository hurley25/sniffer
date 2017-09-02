
#include <QtGui>
#include <QDebug>
#include <vector>
#include <QMessageBox>

#include "choosedevdialog.h"
#include "sniffer.h"
#include "settinginfo.h"

ChooseDevDialog::ChooseDevDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

    pakectByteLimit  = 65535;
    openDevNumber = 0;
    isAutoBegin = beginCheckBox->isChecked();
    isPromiscuous = PromiscuousCheckBox->isChecked();

	this->setFixedSize(this->width(),this->height());

    limitSpinBox->setRange(100, 65535);
    limitSpinBox->setValue(65535);

	setWindowIcon(QIcon(":/res/images/corporation.png"));

	connect(helpButton, SIGNAL(clicked()), this, SLOT(helpDialog()));
	connect(netDevListWidget, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(setChoose(QListWidgetItem *)));
	connect(PromiscuousCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setPromiscuousFlag(int)));
	connect(beginCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setAutoBeginFlag(int)));
	connect(limitSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDataLimitValue(int)));
	connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setFilterString(int)));

	addNetDevInfo();
}

ChooseDevDialog::ChooseDevDialog(Sniffer *sni, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

    pakectByteLimit  = 65535;
    openDevNumber = 0;
	sniffer     = sni;

	this->setFixedSize(this->width(),this->height());

    limitSpinBox->setRange(100, 65535);
    limitSpinBox->setValue(65535);
    pakectByteLimit  = 65535;
    openDevNumber = 0;
    isAutoBegin = beginCheckBox->isChecked();
    isPromiscuous = PromiscuousCheckBox->isChecked();

	setWindowIcon(QIcon(":/res/images/corporation.png"));

	connect(helpButton, SIGNAL(clicked()), this, SLOT(helpDialog()));
	connect(netDevListWidget, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(setChoose(QListWidgetItem *)));
	connect(PromiscuousCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setPromiscuousFlag(int)));
	connect(beginCheckBox, SIGNAL(stateChanged(int)), this, SLOT(setAutoBeginFlag(int)));
	connect(limitSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setDataLimitValue(int)));
	connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setFilterString(int)));

	addNetDevInfo();
}

void ChooseDevDialog::addNetDevInfo()
{
    sniffer->updateDevList();
    for (const NetDevInfo & dev : sniffer->netDevInfo) {
        QListWidgetItem *elem = new QListWidgetItem(
                    QIcon(":/res/images/corporation.png"),
                    QString("Interface: ") + QString(dev.name.c_str())
                    + QString(dev.describe.c_str()), netDevListWidget);
		elem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
		elem->setCheckState(Qt::Unchecked);
        devItemVector.push_back(elem);
        if(dev.ipv4addr != "")
        {
            elem = new QListWidgetItem(QString(dev.ipv4addr.c_str()), netDevListWidget);
            elem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        }
        if(dev.ipv6addr != "")
        {
            elem = new QListWidgetItem(QString(dev.ipv6addr.c_str()), netDevListWidget);
            elem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
        }
    }
}

void ChooseDevDialog::GetUserSet(SettingInfo *settingInfo)
{
    settingInfo->openDevNumber  = openDevNumber;
    settingInfo->isPromiscuous = isPromiscuous;
    settingInfo->autoBegin   = isAutoBegin;
    settingInfo->packetSizeLimit   = pakectByteLimit;
	settingInfo->filterString = filterString;
}

void ChooseDevDialog::setChoose(QListWidgetItem *changedElem)
{
    openDevNumber = 0;
	
	int i = 1;
	if (changedElem->checkState() == Qt::Checked)
	{
		for (std::vector<QListWidgetItem *>::iterator index = devItemVector.begin();
			index < devItemVector.end(); ++index) {
			if (*index != changedElem) {
				(*index)->setCheckState(Qt::Unchecked);
			} else {
                openDevNumber = i;
			}
			i++;
		}
	}
}

void ChooseDevDialog::setPromiscuousFlag(int flag)
{
    isPromiscuous = (flag == Qt::Checked);
}

void ChooseDevDialog::setAutoBeginFlag(int flag)
{
    isAutoBegin = (flag == Qt::Checked);
}

void ChooseDevDialog::setDataLimitValue(int iValue)
{
    pakectByteLimit = iValue;
}

void ChooseDevDialog::setFilterString(int index)
{
    const char * filters[] = {
        "", "ip", "ip6", "tcp",
        "udp", "tcp or  udp", "not arp", "arp",
        "not arp and not tcp and not udp", "port 80"
    };
    if (index < 10)
        filterString = filters[index];
    qDebug() << filterString.c_str() << "Filter Strings" << index;
}

void ChooseDevDialog::helpDialog()
{
    QMessageBox::information(this, tr("Infomation -- Choose A Network Adapter"),
                tr("<p><font size=4> The items of the above list are the activate network adapter"
                   " on your computer. To capture packets you must choose one of them,</font></p>"
                   "<p><font size=4>&nbsp;&nbsp;&nbsp; * Notice: the IP address of the adapter "
                   "maybe helpful to dertemine which one is suitable</font></p>"
                    ));
}
