QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requestdispatcherthread.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    requestdispatcherthread.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h

EXAMPLE_FILES += fileclient.html

