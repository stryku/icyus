#-------------------------------------------------
#
# Project created by QtCreator 2016-08-14T20:44:00
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++1y

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icyus
TEMPLATE = app

INCLUDEPATH += ../../inc

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../src/internals/view/detail/QtWidgetManager.cpp \
    ../../src/internals/view/QtView.cpp \
    ../../src/internals/view/View.cpp

HEADERS  += mainwindow.hpp \
    ../../inc/internals/view/detail/QtWidgetManager.hpp \
    ../../inc/internals/view/QtView.hpp \
    ../../inc/internals/view/View.hpp \
    ../../inc/internals/view/detail/QtViewControls.hpp

FORMS    += mainwindow.ui \
    form.ui
