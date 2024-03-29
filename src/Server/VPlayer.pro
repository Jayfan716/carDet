QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = VPlayer
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    tcpserver.cpp \
    tcpthread.cpp

HEADERS += \
        mainwindow.h \
    tcpserver.h \
    tcpthread.h

FORMS += \
        mainwindow.ui
