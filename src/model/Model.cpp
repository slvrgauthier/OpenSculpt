/*
 * Model.cpp
 * @author : GAUTHIER Silvère
 *
 * Definition file of Model.h.
 *
 */

#include "model/Model.h"
#include "model/func.h"
#include <GL/glut.h>

Model::Model(QWidget *parent):
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer)
{}

void Model::initializeGL() { this->initializeGL(); }
void Model::paintGL() { this->paintGL(); }

QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
