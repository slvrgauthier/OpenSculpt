#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:18:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenScupt
TEMPLATE = app


SOURCES += main.cpp\
        fenprincipal.cpp \
    initialisationmodele.cpp \
    parametragemodele.cpp

HEADERS  += fenprincipal.h \
    initialisationmodele.h \
    parametragemodele.h

FORMS    += fenprincipal.ui \
    initialisationmodele.ui \
    parametragemodele.ui

RESOURCES += \
    ressources.qrc
