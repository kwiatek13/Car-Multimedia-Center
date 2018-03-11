#-------------------------------------------------
#
# Project created by QtCreator 2015-08-26T01:46:08
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = car_multimedia_center_2
TEMPLATE = app
CONFIG += c++11, exceptions


SOURCES += main.cpp\
        dialog.cpp \
    playlist.cpp \
    player.cpp

HEADERS  += dialog.h \
    playlist.h \
    player.h

FORMS    += dialog.ui

INSTALLS        = target
target.files    = widgettest
target.path     = /home/pi
