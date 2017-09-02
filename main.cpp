#include <QtGui>
#include <QApplication>
#include <QTranslator>
#include <QSplashScreen>
#include <QPixmap>
#include <ctime>
#include <QDebug>

#include "mainwindow.h"

//#define SPLASH


int main(int argc, char *argv[])
{
	QTextCodec *codec = QTextCodec::codecForName("system");

	QTextCodec::setCodecForLocale(codec);

	QApplication app(argc, argv);
//	QTranslator translator;

//	translator.load(":/res/language/qt_zh_CN.qm");
//	app.installTranslator(&translator);

#ifdef SPLASH
    QSplashScreen *splash = new QSplashScreen;
	splash->setPixmap(QPixmap(":/res/images/startlogo.png"));
	splash->show();
#endif

	MainWindow *mainwindow = new MainWindow;
	mainwindow->sleep(1000);
	mainwindow->showMaximized();

#ifdef SPLASH
	splash->finish(mainwindow);
	delete splash;
#endif

	return app.exec();
}

