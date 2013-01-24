# =====================================================================================
# 
#       Filename:  sniffer_win32.pro
#
#    Description:  为 Win32 环境书写的 Qt 项目文件
#
#        Created:  2013年01月24日 14时05分02秒
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
RC_FILE = logo.rc

# Input
HEADERS += csniffer.h listtreeview.h mainwindow.h sniffertype.h
SOURCES += csniffer.cpp listtreeview.cpp main.cpp mainwindow.cpp
RESOURCES += sniffer.qrc

