#-------------------------------------------------
#
# Project created by Umesh Kumar Patel 2014-10-20
#
# [github] = https://github.com/umeshkpatel
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = AdvanceCPP
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    src/logging/ULogging.cc

HEADERS += \
    include/UBasics.h \
    include/UDefines.h \
    include/ULogging.h \
    include/utl/USmartPtr.h \
    include/utl/UStack.h

INCLUDEPATH += \
    include/
