
#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QMainWindow>

#include "settinginfo.h"

class QAction;
class QLabel;
class QSplitter;
class QTextEdit;
class CapTableView;
class QTreeView;
class QStandardItemModel;
class QTemporaryFile;
class QItemSelection;
class QLineEdit;

class CaptureThread;
class Sniffer;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow();

    void sleep(unsigned int msec);

    SettingInfo *settingInfo;

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void newFile();
    void open();
    void save();
	void chooseDev();
	void begin();
	void end();
	void about();
    void filterChanged(const QString & filter);
    void applyFilter();
    void updateAnalysisTree(const QItemSelection &nowSelect);

private:

    void createMainWeiget();
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
	
    void readSettings();
    void writeSettings();

    int isToContinue();

    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

    CaptureThread *captureThread;

    Sniffer *sniffer;

    QSplitter *rightSplitter;
    QSplitter *captureSplitter;

    CapTableView *captureTreeView;
//    ProtoTreeView *protocolTreeView;
    QTreeView * protocolTree;

    QTextEdit *explainEdit;
    QTextEdit *hexEdit;
    QLineEdit *filterEdit;

    QLabel *statusLabel;
	
    QMenu *fileMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;

    QToolBar *toolBar;

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;

    QAction *chooseDevAction;
    QAction *beginAction;
    QAction *endAction;

    QAction *applyFilterAction;

    QAction *aboutAction;
};

#endif // MAINWINDOW_H_
