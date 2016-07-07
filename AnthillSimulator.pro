#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T19:33:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnthillSimulator
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    menu.cpp \
    anthill.cpp \
    world.cpp \
    groupant.cpp \
    antqueen.cpp \
    antmale.cpp \
    antfemale.cpp \
    sectordialog.cpp \
    info.cpp

HEADERS  += mainwindow.h \
    menu.h \
    anthill.h \
    world.h \
    ant.h \
    groupant.h \
    antqueen.h \
    antmale.h \
    antfemale.h \
    sectordialog.h \
    info.h

FORMS    += mainwindow.ui \
    menu.ui \
    sectordialog.ui \
    info.ui

RESOURCES += \
    resource.qrc
