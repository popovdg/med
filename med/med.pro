#-------------------------------------------------
#
# Project created by QtCreator 2016-10-27T16:10:38
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QMAKE_LFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -stdlib=libc++

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = med
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    patientsitemdelegate.cpp

HEADERS  += mainwindow.h \
    patientsitemdelegate.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc
