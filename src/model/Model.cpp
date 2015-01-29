/*
 * Model.cpp
 * @author : Team OpenSculpt
 *
 * Definition file of Model.h.
 *
 */

#include "model/Model.h"
#include "model/func.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#endif

Model::Model(QWidget *parent):
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer)
{}

//void Model::initializeGL() { this->initializeGL(); }
//void Model::paintGL() { this->paintGL(); }

QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
