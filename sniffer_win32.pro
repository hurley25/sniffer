# =====================================================================================
# 
#       Filename:  sniffer_win32.pro
#
#    Description:  为 Win32 环境书写的 Qt 项目文件
#
#        Created:  2013年01月22日 14时05分02秒
#
#         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
#        Company:  Class 1107 of Computer Science and Technology
#
# =====================================================================================

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
INCLUDEPATH += winpcap

# Input
HEADERS += csniffer.h listtreeview.h mainwindow.h sniffertype.h \
			sniffer.h capturethread.h choosedevdialog.h settinginfo.h \
			findqqdialog.h

SOURCES += csniffer.cpp listtreeview.cpp main.cpp mainwindow.cpp \
			sniffer.cpp capturethread.cpp choosedevdialog.cpp	\
			findqqdialog.cpp

FORMS += choosedevdialog.ui findqqdialog.ui

RESOURCES += sniffer.qrc
RC_FILE = logo.rc
