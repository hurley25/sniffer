# =====================================================================================
# 
#       Filename:  sniffer_linux.pro
#
#    Description:  为 Linux 环境书写的 Qt 项目文件
#
#        Created:  2013年02月01日 15时54分02秒
#
#         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
#        Company:  Class 1107 of Computer Science and Technology
#
# =====================================================================================

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input

LIBS += -lpcap

HEADERS +=  include/csniffer.h include/listtreeview.h include/mainwindow.h include/sniffertype.h \
			include/sniffer.h include/capturethread.h include/choosedevdialog.h include/settinginfo.h \
			include/findqqdialog.h include/findqqthread.h include/prototreeview.h

SOURCES +=  src/main.cpp src/csniffer.cpp src/listtreeview.cpp src/mainwindow.cpp \
			src/sniffer.cpp src/capturethread.cpp src/choosedevdialog.cpp \
			src/findqqdialog.cpp src/findqqthread.cpp src/prototreeview.cpp

FORMS += ui/choosedevdialog.ui ui/findqqdialog.ui

RESOURCES += sniffer.qrc
