#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T08:34:48
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = AdvanceCPP
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    src/logging/ULogging.cc \
    main.cpp

HEADERS += \
    include/UDefines.h \
    include/ULogging.h \
    include/utl/USmartPtr.h \
    include/utl/UStack.h

INCLUDEPATH += \
    include/
