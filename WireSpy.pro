QT += widgets
# QT += printsupport

QMAKE_CXXFLAGS+=-std=c++11

TEMPLATE = app
# TARGET =
DEPENDPATH += ./


LIBS += -lpcap

HEADERS +=  csniffer.h mainwindow.h sniffertype.h \
                        sniffer.h capturethread.h choosedevdialog.h settinginfo.h \
    analysisthread.h \
    common.h \
    protocolnames.h \
    protocolitem.h \
    protocolmodel.h \
    captureview.h

SOURCES +=  main.cpp csniffer.cpp mainwindow.cpp \
                        sniffer.cpp capturethread.cpp choosedevdialog.cpp \
    analysisthread.cpp \
    common.cpp \
    protocolnames.cpp \
    protocolitem.cpp \
    protocolmodel.cpp \
    captureview.cpp

FORMS += ui/choosedevdialog.ui

RESOURCES += wirespy.qrc

ICON = icon.icns
