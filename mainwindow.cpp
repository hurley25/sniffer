#include <QtGui>
#include <QMessageBox>
#include <QEvent>
#include <QCloseEvent>
#include <QFileDialog>
#include <QStatusBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QSplitter>
#include <QMenuBar>
#include <QToolBar>
#include <QDebug>
#include <QWidget>
#include <QTreeView>
#include <QStyleFactory>

#include "mainwindow.h"
#include "captureview.h"
#include "capturethread.h"
#include "choosedevdialog.h"
#include "sniffer.h"
#include "protocolmodel.h"

MainWindow::MainWindow()
{
    captureThread = NULL;

    sniffer = Sniffer::get_sniffer();
    if (sniffer->updateDevList() == false)
    {
        QMessageBox::warning(
                    this, tr("WireSpy"),
                    tr("<H3>Can't Open the Network Interface。</H3>"
                       "<p>Some Possible Reasons：\n"
                       "<p>1. Unspported Network Card, Reffer to <a href=\"http://winpcap.org\">"
                       "http://winpcap.org</a>\n"
                       "<p>2. Permission denied:\n"
                       "<p>&nbsp;&nbsp;&nbsp;&nbsp;try `sudo chgrp admin /dev/bpf*`\n"
                       "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`sudo chmod g+rw /dev/bpf*`"
                       "<p>3. Being Stopped By the Antivirus software or HIPS."), QMessageBox::Ok);
    }

    settingInfo = new SettingInfo;

    createMainWeiget();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();

    setWindowIcon(QIcon(":/res/ico/main.png"));
    setWindowTitle(tr("WireSpy"));
}

MainWindow::~MainWindow()
{
    if (this->captureThread != NULL)
        this->captureThread->stop();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int res = this->isToContinue();
    if (res == QMessageBox::Yes)
    {
        save();
        writeSettings();
        event->accept();
    }
    else if (res == QMessageBox::No)
    {
        writeSettings();
        event->accept();
    }
    else if (res == QMessageBox::Cancel)
    {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    auto flag = isToContinue();
    if ( flag == QMessageBox::No)
    {
        captureTreeView->resetInfo();
        setCurrentFile("");
    }
    else if (flag == QMessageBox::Yes)
    {
        save();
    }
}

void MainWindow::open()
{
    auto flag = isToContinue();
    if (flag == QMessageBox::No)
    {
        QString fileName = QFileDialog::getOpenFileName
                (this, tr("open"), ".",tr("WireSpy PCAP File (*.pcap)"));
        if(fileName.isEmpty())
            return;
        if (loadFile(fileName))
        {
            this->captureTreeView->resetInfo();
            captureThread->start();
        }
        else
        {
            QMessageBox::warning(this, tr("WireSpy"),
                                 tr("<H3>Open File Failed"), QMessageBox::Ok);
        }
    }
    else
        save();
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("Save As ..."), ".",
                tr("WireSpy PCAP File (*.pcap)"));
    if (!fileName.isEmpty())
    {
        saveFile(fileName);
    }
}

void MainWindow::chooseDev()
{
    ChooseDevDialog chooseDevDialog(sniffer, this);
    if (chooseDevDialog.exec() == QDialog::Accepted)
    {
        chooseDevDialog.GetUserSet(settingInfo);
        if (settingInfo->openDevNumber <= 0)
            return;
        if (settingInfo->autoBegin == true)
            begin();
        else
            beginAction->setEnabled(true);
    }
}

void MainWindow::begin()
{
    int dataCount = captureTreeView->haveData();
    if (dataCount > 0)
    {
        int result = QMessageBox::warning(
                    this, tr("WireSpy"),
                    tr("<H3>We've Already Captured %1 Packets。</H3>"
                       "Are You Sure to Discard Them？").arg(QString::number(dataCount)),
                    QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::No)
            return;
        captureTreeView->resetInfo();
    }
    if (captureThread != NULL)
        captureThread->stop();

    QDateTime nowTime   = QDateTime::currentDateTime();
    QString tmpFileName = QDir::tempPath() + "/pcap" + nowTime.toString("yyyy-MM-dd-hh-mm-ss") + ".tmp";

    setCurrentFile(tmpFileName);
    if (captureThread != NULL)
        captureThread->reset(captureTreeView, tmpFileName);
    else
        captureThread = new CaptureThread(captureTreeView, tmpFileName);

    bool isOpenSuccess = false;
    if (settingInfo->isPromiscuous)
    {
        isOpenSuccess = sniffer->openNetDev(
                    settingInfo->openDevNumber,
                    PCAP_OPENFLAG_PROMISCUOUS, settingInfo->packetSizeLimit);
    }
    else
    {
        isOpenSuccess = sniffer->openNetDev(
                    settingInfo->openDevNumber,PCAP_OPENFLAG_NOCAPTURE_LOCAL,
                    settingInfo->packetSizeLimit);
    }

    if (isOpenSuccess)
    {
        sniffer->setDevsFilter(settingInfo->filterString.c_str());
        captureThread->start();
        chooseDevAction->setEnabled(false);
        beginAction->setEnabled(false);
        endAction->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(
                    this, tr("WireSpy"),
                    tr("<H3>Can't Open the Network Interface。</H3>"
                       "<p>Some Possible Reasons：\n"
                       "<p>1. Unspported Network Card, Reffer to <a href=\"http://winpcap.org\">"
                       "http://winpcap.org</a>\n"
                       "<p>2. Permission denied:\n"
                       "<p>&nbsp;&nbsp;&nbsp;&nbsp;try `sudo chgrp admin /dev/bpf*`\n"
                       "<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`sudo chmod g+rw /dev/bpf*`"
                       "<p>3. Being Stopped By the Antivirus software or HIPS."), QMessageBox::Ok);
    }
}

void MainWindow::end()
{
    chooseDevAction->setEnabled(true);
    beginAction->setEnabled(true);
    endAction->setEnabled(false);
    captureThread->stop();
    if (captureTreeView->haveData())
    {
        saveAction->setEnabled(true);
    }
}

void MainWindow::readSettings()
{
    QSettings settings("WireSpy.ini", QSettings::IniFormat);

    settingInfo->openDevNumber  = settings.value("iOpenDevNum", true).toInt();
    settingInfo->isPromiscuous = settings.value("bPromiscuous", true).toBool();
    settingInfo->autoBegin   = settings.value("bAutoBegin", true).toBool();
}

void MainWindow::writeSettings()
{
    QSettings settings("WireSpy.ini", QSettings::IniFormat);
    settings.setValue("iOpenDevNum", settingInfo->openDevNumber);
    settings.setValue("bPromiscuous", settingInfo->isPromiscuous);
    settings.setValue("bAutoBegin", settingInfo->autoBegin);
}

bool MainWindow::loadFile(const QString &fileName)
{
    bool fileOpenFlag = sniffer->openOffline(fileName.toStdString().c_str());
    QDateTime nowTime   = QDateTime::currentDateTime();
    QString tmpFileName = QDir::tempPath() + "/WireSpy-" + nowTime.toString("yyyyMMddhhmmss") + ".tmp";
    if (captureThread != NULL)
    {
        captureThread->stop();
        captureThread->reset(this->captureTreeView, tmpFileName);
    }
    else
        captureThread = new CaptureThread(this->captureTreeView, tmpFileName);
    setCurrentFile(tmpFileName);
    if (fileOpenFlag == true)
    {
        qDebug() << "Filter" << settingInfo->filterString.c_str();
        sniffer->setDevsFilter(settingInfo->filterString.c_str());
    }
    return fileOpenFlag;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!sniffer->dumpFlush())
        return false;
    if (!QFile::copy(QString(sniffer->getDumpFileName()), fileName))
    {
        QMessageBox::warning(this, tr("WireSpy"),
                             tr("<H3>Saving File Failed。</H3>"), QMessageBox::Ok);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    if (!fileName.isEmpty())
    {
        statusLabel->setText(fileName);
    }
    else
    {
        saveAction->setEnabled(false);
        statusLabel->setText("WireSpy");
    }
}

void MainWindow::updateAnalysisTree(const QItemSelection &nowSelect)
{
    QModelIndexList items = nowSelect.indexes();
    QModelIndex     index = items.first();

    QString strNumber;
    captureTreeView->getOrderNumber(index, strNumber);

    int number = strNumber.toInt();
    if ((unsigned int)number < sniffer->getPacketsCount())
    {
        vector<string> infos;
        this->sniffer->analyse(number, infos);

        explainEdit->setText(sniffer->getExplainText(number));
        hexEdit->setText(sniffer->getHexText(number));

        ProtocolModel * ptrmodel = new ProtocolModel(QString("Protocol Analysis"), infos);
        QAbstractItemModel *tmpmdl = protocolTree->model();
        protocolTree->setModel(ptrmodel);
        delete tmpmdl;
        protocolTree->expandToDepth(1);
        protocolTree->setStyle(QStyleFactory::create("Windows"));
        protocolTree->setColumnWidth(0,1000);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About WireSpy"),
                       tr("<h2>WireSpy</h2>"
                          "<p>Copyright (C) 2017 UCAS"
                          "<p>A Simple Network Sniffer"));
}


void MainWindow::applyFilter()
{
    this->filterChanged(this->filterEdit->text());
    if(sniffer->haveDevHandle() &&
            sniffer->checkCaptureFilter(this->filterEdit->text().toStdString().c_str()))
    {
        this->captureThread->stop();
        this->captureTreeView->resetInfo();
        this->settingInfo->filterString = this->filterEdit->text().toStdString();
        this->begin();
    }
    //    qDebug() << "Applying Filter" << this->filterEdit->text() << endl;
    //    return sniffer->setDevsFilter(filter);
}

int MainWindow::isToContinue()
{
    if (captureTreeView->haveData())
    {
        return QMessageBox::question(NULL, tr("WireSpy"),
                                     tr("<H3>We've Already Captured Some Packet Data。</H3>"
                                        "Would You Like to Save It to Hard Drive Disk？"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    }
    return QMessageBox::No;
}

void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while ( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void MainWindow::createMainWeiget()
{
    captureTreeView = new CapTableView;
    protocolTree = new QTreeView;
    explainEdit = new QTextEdit;
    hexEdit = new QTextEdit;
    filterEdit = new QLineEdit;
    filterEdit->setCursor(QCursor(Qt::IBeamCursor));

    QFont font = QFont("Courier", 14);

    explainEdit->setReadOnly(true);
    explainEdit->setCurrentFont(font);
    explainEdit->setMaximumWidth(160);
    explainEdit->setWordWrapMode(QTextOption::WrapAnywhere);
    explainEdit->setWindowTitle(tr("Original ASCII DATA"));
    explainEdit->setLineWrapMode(QTextEdit::NoWrap);

    hexEdit->setReadOnly(true);
    hexEdit->setCurrentFont(font);
    hexEdit->setMaximumWidth(300);
    hexEdit->setWindowTitle(tr("Original Hex Data"));
    hexEdit->setLineWrapMode(QTextEdit::NoWrap);
    //    originalEdit->setFixedWidth(font.pointSize()*32);
    QFontMetricsF fmt = QFontMetricsF(font);
    //    originalEdit->setFixedWidth(fmt.width(QString("0123456789123456"))*2 + 2);
    //    explainEdit->setFixedWidth(fmt.width(QString("0123456789123456")) + 2);
    //    originalEdit->setLineWidth(32);
    QString style = "QTextEdit{font-size:12px;max-width:16em;background-color: #eee;}";
    //    originalEdit->setStyleSheet(style);

    filterEdit->setFixedHeight(24);
    filterEdit->setPlaceholderText(tr("Set A New Capture Filter"));
    filterEdit->setFont(QFont("Courier", 12));

    rightSplitter = new QSplitter(Qt::Vertical);

    QSplitter * rightDownSplitter =  new QSplitter(Qt::Horizontal);
    rightDownSplitter->addWidget(hexEdit);
    rightDownSplitter->addWidget(explainEdit);

    rightSplitter->addWidget(protocolTree);
    rightSplitter->addWidget(rightDownSplitter);

    captureSplitter = new QSplitter(Qt::Horizontal);
    QSplitter * centerSplitter = new QSplitter(Qt::Vertical);

    centerSplitter->addWidget(filterEdit);
    centerSplitter->addWidget(captureTreeView);
    captureSplitter->addWidget(centerSplitter);
    captureSplitter->addWidget(rightSplitter);

    this->setCentralWidget(captureSplitter);

    connect(captureTreeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(updateAnalysisTree(const QItemSelection &)));
    connect(this->filterEdit,SIGNAL(textChanged(const QString &)),
            this, SLOT(filterChanged(const QString&)));
    connect(this->filterEdit, SIGNAL(returnPressed()),
            this, SLOT(applyFilter()));
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("Recapture"), this);
    newAction->setIcon(QIcon(":/res/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Recapture and Clear the History"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openAction = new QAction(tr("Open"), this);
    openAction->setIcon(QIcon(":/res/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open A PCAP File"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("Save"), this);
    saveAction->setIcon(QIcon(":/res/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the Captured Packets to A PCAP File"));
    saveAction->setEnabled(false);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    exitAction = new QAction(tr("Quit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Quit Now"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    chooseDevAction = new QAction(tr("Choose Interface"), this);
    chooseDevAction->setIcon(QIcon(":/res/images/wifi.png"));
    chooseDevAction->setShortcut(tr("Ctrl+N"));
    chooseDevAction->setStatusTip(tr("Choose A Interface to Capture"));
    connect(chooseDevAction, SIGNAL(triggered()), this, SLOT(chooseDev()));

    beginAction = new QAction(tr("Begin"), this);
    beginAction->setIcon(QIcon(":/res/images/begin.png"));
    beginAction->setShortcut(tr("Ctrl+B"));
    beginAction->setStatusTip(tr("Begin to Capture"));
    beginAction->setEnabled(false);
    connect(beginAction, SIGNAL(triggered()), this, SLOT(begin()));

    endAction = new QAction(tr("Stop"), this);
    endAction->setIcon(QIcon(":/res/images/end.png"));
    endAction->setShortcut(tr("Ctrl+E"));
    endAction->setStatusTip(tr("Stop Capturing"));
    endAction->setEnabled(false);
    connect(endAction, SIGNAL(triggered()), this, SLOT(end()));

    applyFilterAction = new QAction(tr("Aplly"), this);
    //    applyFilterAction->setIconText("Apply");
    applyFilterAction->setIcon(QIcon(":/res/images/filter.png"));
    applyFilterAction->setShortcut(tr("Ctrl+F"));
    applyFilterAction->setStatusTip(tr("Applying New Filter"));
    applyFilterAction->setEnabled(true);
    connect(applyFilterAction, SIGNAL(triggered()), this, SLOT(applyFilter()));
    filterEdit->addAction(applyFilterAction, QLineEdit::TrailingPosition);

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setIcon(QIcon(":/res/images/about.png"));
    aboutAction->setStatusTip(tr("About Infos"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = this->menuBar()->addMenu(tr("File"));
    //    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);

    fileMenu->addSeparator();

    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    toolsMenu = this->menuBar()->addMenu(tr("Capture"));
    toolsMenu->addAction(chooseDevAction);
    //    toolsMenu->addSeparator();
    toolsMenu->addAction(beginAction);
    toolsMenu->addAction(endAction);
    toolsMenu->addSeparator();

    this->menuBar()->addSeparator();

    helpMenu = this->menuBar()->addMenu(tr("Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
    toolBar = new QToolBar("File", this);
    toolBar->setMovable(false);

    //    toolBar->addAction(newAction);
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    //    toolBar->addSeparator();
    toolBar->addAction(chooseDevAction);
    toolBar->addAction(beginAction);
    toolBar->addAction(endAction);
    this->addToolBar(Qt::LeftToolBarArea, toolBar);
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel("WireSpy");
    statusLabel->setAlignment(Qt::AlignHCenter);
    statusLabel->setMinimumSize(statusLabel->sizeHint());

    this->statusBar()->addWidget(statusLabel);
}


void MainWindow::filterChanged(const QString &filter){
    const char * str = filter.toStdString().c_str();
    if(!sniffer->haveDevHandle())
        this->filterEdit->setStyleSheet("QLineEdit { background: rgb(255, 255, 0);}");
    else if(sniffer->checkCaptureFilter(str))
        this->filterEdit->setStyleSheet("QLineEdit { background: rgb(0, 255, 0);}");
    else
        this->filterEdit->setStyleSheet("QLineEdit { background: rgb(255, 0, 0);}");
}
