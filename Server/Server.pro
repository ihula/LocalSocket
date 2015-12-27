#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T22:21:27
#
#-------------------------------------------------

QT       += core gui
QT       += dbus
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hlocalserver.cpp

HEADERS  += mainwindow.h \
    hlocalserver.h

FORMS    += mainwindow.ui
