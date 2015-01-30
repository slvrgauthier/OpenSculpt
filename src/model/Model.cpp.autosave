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
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

Model::Model():
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer)
{}

QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
QVector3D Model::getVertex(int index) const { return m_vertices.at(index); }
void Model::setVertex(int index, QVector3D vertex) { m_vertices.replace(index, vertex); }
int Model::getSize() const { return m_vertices.size(); }

void Model::update()
{
    m_vertexbuffer.bind();
    m_vertexbuffer.write(0, m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();
}

void Model::scale(float percent)
{

}

void Model::setWidth(float width){}
void Model::setHeight(float height){}
void Model::setDepth(float depth){}
