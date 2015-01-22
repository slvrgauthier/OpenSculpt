#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:18:42
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSculpt
TEMPLATE = app


SOURCES += main.cpp\
    gui/fenprincipal.cpp \
    gui/initialisationmodele.cpp \
    gui/parametragemodele.cpp \
    gui/glwidget.cpp \
    model/VBOManager.cpp

HEADERS += gui/fenprincipal.h \
    gui/initialisationmodele.h \
    gui/parametragemodele.h \
    gui/glwidget.h \
    model/VBOManager.h

FORMS += gui/fenprincipal.ui \
    gui/initialisationmodele.ui \
    gui/parametragemodele.ui

RESOURCES += \
    data/ressources.qrc

macx:QMAKE_LIBS_OPENGL += -framework GLUT -lobjc
//QMAKE_LIBS_OPENGL += -lGL -lGLU -lglut -lm
