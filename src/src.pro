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

# Inlcude Botan
include($${PWD}/botan.pri)

INCLUDEPATH += $${QUAZIPCODEDIR}
INCLUDEPATH += $${ZLIBCODEDIR}

CONFIG += c++11

unix {
    LIBS += -L$${QUAZIPCODEDIR} -lquazip -lz
}

win32 {
    LIBS += -L$${QUAZIPCODEDIR} -lquazipdll -lzdll
}

SOURCES += main.cpp\
    compress.cpp \
    mainwindow.cpp \
    filedialog.cpp \
    dropdownbutton.cpp \
    botanwrapper.cpp

HEADERS += compress.h \
    mainwindow.h \
    filedialog.h \
    dropdownbutton.h \
    botanwrapper.h

FORMS += mainwindow.ui

RESOURCES += \
    resources.qrc
