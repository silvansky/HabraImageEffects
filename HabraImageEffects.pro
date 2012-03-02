#-------------------------------------------------
#
# Project created by QtCreator 2012-03-02T14:09:23
#
#-------------------------------------------------

QT       += core gui network

TARGET = HabraImageEffects
TEMPLATE = app


SOURCES += main.cpp\
        habrawidget.cpp \
    imagemanager.cpp \
    networking.cpp

HEADERS  += habrawidget.h \
    imagemanager.h \
    networking.h \
    networking_p.h

FORMS    += habrawidget.ui

RESOURCES += \
    images.qrc
