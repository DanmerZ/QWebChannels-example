#-------------------------------------------------
#
# Project created by QtCreator 2016-07-08T23:32:21
#
#-------------------------------------------------

QT       += core gui webchannel

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets

TARGET = TestWebEngine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    object.cpp

HEADERS  += mainwindow.h \
    object.h

FORMS    += mainwindow.ui

DISTFILES += \
    index.html

RESOURCES += \
    res.qrc
