#-------------------------------------------------
#
# Project created by QtCreator 2011-12-28T14:43:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = openCV


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

PKGCONFIG += opencv
CONFIG += link_pkgconfig