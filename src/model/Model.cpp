/*
 * Model.cpp
 * @author : Team OpenSculpt
 *
 * Definition file of Model.h.
 *
 */

#include "model/Model.h"
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
    m_indicebuffer(QGLBuffer::IndexBuffer),
    m_center(QVector3D(0.0,0.0,0.0))
{}

QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
QVector3D Model::getVertex(int index) const { return m_coords.at(index); }
void Model::setVertex(int index, QVector3D vertex) { m_vertices[index].coords = vertex; m_coords[index] = vertex; }
int Model::getSize() const { return m_vertices.size(); }
QVector3D Model::getCenter() const { return m_center; }
void Model::setCenter(QVector3D center) { m_center = center; }

void Model::convertToBuffer()
{
    // Convertir le maillage interne pour le rendu
    m_coords.clear();
    m_coords.reserve(m_vertices.size());
    for(int i=0 ; i < m_vertices.size() ; ++i) {
        m_coords.push_back(m_vertices[i].coords);
    }

    m_indices.clear();
    m_indices.reserve(m_faces.size() * 3);
    for(int i=0 ; i < m_faces.size() ; ++i) {
        m_indices.push_back(m_faces[i].edge->vertex->index);
        m_indices.push_back(m_faces[i].edge->next->vertex->index);
        m_indices.push_back(m_faces[i].edge->previous->vertex->index);
    }
}

void Model::update()
{
    // Vertex buffer init
    if(m_vertexbuffer.isCreated() && m_vertexbuffer.size() >= m_coords.size()) {
        m_vertexbuffer.bind();
        m_vertexbuffer.write(0, m_coords.constData(), m_coords.size() * sizeof(QVector3D));
        m_vertexbuffer.release();
    }
    else {
        m_vertexbuffer.destroy();
        m_vertexbuffer.create();
        m_vertexbuffer.bind();
        m_vertexbuffer.allocate(m_coords.constData(), m_coords.size() * sizeof(QVector3D));
        m_vertexbuffer.release();
    }

    // Indices buffer init
    if(m_indicebuffer.isCreated() && m_indicebuffer.size() >= m_indices.size()) {
        m_indicebuffer.bind();
        m_indicebuffer.write(0, m_indices.constData(), m_indices.size() * sizeof(GLuint));
        m_indicebuffer.release();
    }
    else {
        m_indicebuffer.destroy();
        m_indicebuffer.create();
        m_indicebuffer.bind();
        m_indicebuffer.allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));
        m_indicebuffer.release();
    }
}

void Model::scale(float percent)
{

}

void Model::setWidth(float width){}
void Model::setHeight(float height){}
void Model::setDepth(float depth){}
