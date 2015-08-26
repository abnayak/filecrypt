#-------------------------------------------------
#
# Project created by QtCreator 2015-07-18T09:42:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = filecrypt
TEMPLATE = app

QUAZIPCODEDIR += $${PWD}/../quazip/
ZLIBCODEDIR += $${PWD}/../zlib/

INCLUDEPATH += $${QUAZIPCODEDIR}
INCLUDEPATH += $${ZLIBCODEDIR}

unix {
    LIBS += -L$${QUAZIPCODEDIR} -lquazip -lz
}

win32 {
    LIBS += -L$${QUAZIPCODEDIR} -lquazipdll -lzdll
}

SOURCES += main.cpp\
    mainwindow.cpp \
    filedialog.cpp \
    encrypt.cpp \
    compress.cpp \
    dropdownbutton.cpp

HEADERS += mainwindow.h \
    filedialog.h \
    encrypt.h \
    compress.h \
    dropdownbutton.h

FORMS += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../../../Downloads/Folder-26.png
