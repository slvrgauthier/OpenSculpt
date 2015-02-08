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
    gui/glwidget.cpp \
    mesh/Mesh.cpp \
    mesh/MeshRenderer.cpp \
    mesh/MeshProcessing.cpp \
    mesh/MeshManager.cpp \
    mesh/makeCube.cpp \
    mesh/makeCylinder.cpp \
    mesh/makeCone.cpp \
    mesh/makeSphere.cpp \
    mesh/makeTorus.cpp \
    mesh/functions.cpp \
    mesh/MeshTool.cpp

HEADERS += gui/mainWindow.h \
    gui/glwidget.h \
    mesh/Mesh.h \
    mesh/MeshRenderer.h \
    mesh/MeshProcessing.h \
    mesh/HalfEdge.h \
    mesh/MeshManager.h \
    mesh/functions.h \
    mesh/MeshTool.h

FORMS += gui/mainWindow.ui

RESOURCES += \
    data/ressources.qrc

macx:QMAKE_LIBS_OPENGL += -framework GLUT -lobjc
linux:QMAKE_LIBS_OPENGL += -lGL -lGLU -lglut -lm
win32:QMAKE_LIBS_OPENGL += -lopengl32 -lglut32
win32:INCLUDEPATH += "C:\Qt\Qt5.4.0\5.4\mingw491_32\include"
