#-------------------------------------------------
#
# Project created by QtCreator 2015-12-24T23:33:45
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia
QT       += multimediawidgets

QT       -= gui

TARGET =ClientCamera
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += main.cpp \
    hcamera.cpp \
    hlocalsocket.cpp \
    hmanager.cpp

HEADERS += \
    hcamera.h \
    hlocalsocket.h \
    hmanager.h

FORMS +=
