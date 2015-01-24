#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:18:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenScupt
TEMPLATE = app


SOURCES += main.cpp\
        fenprincipal.cpp \
    initialisationmodele.cpp \
    parametragemodele.cpp \
    glwidget.cpp

HEADERS  += fenprincipal.h \
    initialisationmodele.h \
    parametragemodele.h \
    glwidget.h

FORMS    += fenprincipal.ui \
    initialisationmodele.ui \
    parametragemodele.ui

RESOURCES += \
    ressources.qrc

macx:QMAKE_LIBS_OPENGL += -framework GLUT -lobjc

LIBS += -lfreeglut
