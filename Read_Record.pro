#-------------------------------------------------
#
# Project created by QtCreator 2019-03-07T16:06:06
#
#-------------------------------------------------

QT       += core gui
QT       += core gui serialport
QT       += printsupport

CONFIG   += qaxcontainer
RC_FILE = icon.rc
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Read_Record
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    common/CRC16.c \
    transmission.cpp

HEADERS += \
        mainwindow.h \
    common/Common.h \
    common/CRC16.h \
    command.h \
    project_file.h \
    transmission.h

FORMS += \
        mainwindow.ui \
    transmission.ui

QXLSX_PARENTPATH=./
QXLSX_HEADERPATH=./header/
QXLSX_SOURCEPATH=./source/
include(./QXlsx.pri)

DISTFILES += \
    Image/realy.ico
