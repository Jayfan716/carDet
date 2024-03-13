QT          += core gui network
INCLUDEPATH += D:\Academic\GraDesign\opecv4.5.5\install\include
LIBS += D:\Academic\GraDesign\opecv4.5.5\install\x64\mingw\lib\libopencv_*.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = TheStreamer-client
TEMPLATE = app

SOURCES += main.cpp\
        streamerclient.cpp \
    streamerthread.cpp \
    yolo.cpp

HEADERS  += streamerclient.h \
    streamerthread.h \
    yolo.h

FORMS    += streamerclient.ui
