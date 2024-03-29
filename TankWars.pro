#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T15:27:00
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankWars
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        levelobject.cpp \
        interface.cpp \
        levelmanager.cpp \
        unittests.cpp \
        opponentmanager.cpp \
        networkmanager.cpp \
        filemanager.cpp \
        userinformation.cpp

HEADERS  += mainwindow.h \
        levelobject.h \
        interface.h \
        levelmanager.h \
        unittests.h \
        opponentmanager.h \
        networkmanager.h \
        filemanager.h \
        userinformation.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

QT += multimedia

RESOURCES += resources.qrc

DEFINES += QT_NO_DEBUG_OUTPUT
