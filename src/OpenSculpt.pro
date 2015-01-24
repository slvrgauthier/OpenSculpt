#-------------------------------------------------
#
# Project created by QtCreator 2015-01-21T14:18:42
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenSculpt
TEMPLATE = app


SOURCES += main.cpp \
    gui/mainWindow.cpp \
    gui/initModel.cpp \
    gui/settingModel.cpp \
    gui/glwidget.cpp \
    model/VBOManager.cpp \
    model/ModelManager.cpp \
    model/Model.cpp \
    model/heightMap.cpp

HEADERS += gui/mainWindow.h \
    gui/initModel.h \
    gui/settingModel.h \
    gui/glwidget.h \
    model/VBOManager.h \
    model/ModelManager.h \
    model/Model.h \
    func/functions.h \
    model/heightMap.h

FORMS += gui/mainWindow.ui \
    gui/initModel.ui \
    gui/settingModel.ui

RESOURCES += \
    data/ressources.qrc

macx:QMAKE_LIBS_OPENGL += -framework GLUT -lobjc
linux:QMAKE_LIBS_OPENGL += -lGL -lGLU -lglut -lm
win32:QMAKE_LIBS_OPENGL += -lfreeglut
