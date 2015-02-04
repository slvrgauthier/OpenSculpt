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
#include <QDebug>

Model::Model():
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer),
    m_center(QVector3D(0.0,0.0,0.0))
{}

Model::~Model()
{
    for(int i=0 ; i < m_edges.size() ; ++i) {
        delete m_edges[i];
    }
    for(int i=0 ; i < m_vertices.size() ; ++i) {
        delete m_vertices[i];
    }
    for(int i=0 ; i < m_faces.size() ; ++i) {
        delete m_faces[i];
    }
    m_vertexbuffer.destroy();
    m_indicebuffer.destroy();
}

QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
QVector3D Model::getVertex(int index) const { return m_coords.at(index); }
void Model::setVertex(int index, QVector3D vertex) { m_vertices[index]->coords = vertex; m_coords[index] = vertex; }
int Model::getSize() const { return m_vertices.size(); }
QVector3D Model::getCenter() const { return m_center; }
void Model::setCenter(QVector3D center) { m_center = center; }

void Model::convertToBuffer()
{
    // Convertir le maillage interne pour le rendu
    m_coords.clear();
    m_coords.reserve(m_vertices.size());
    for(int i=0 ; i < m_vertices.size() ; ++i) {
        m_coords.push_back(m_vertices[i]->coords);
    }

    m_indices.clear();
    m_indices.reserve(m_faces.size() * 3);
    for(int i=0 ; i < m_faces.size() ; ++i) {
        m_indices.push_back(m_faces[i]->edge->vertex->index);
        m_indices.push_back(m_faces[i]->edge->next->vertex->index);
        m_indices.push_back(m_faces[i]->edge->previous->vertex->index);
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

void Model::subdivide()
{
    TEST();
    m_faces.reserve(4 * m_faces.size());
    m_edges.reserve(m_edges.size() + 9*m_faces.size());
    m_vertices.reserve(m_vertices.size() + 3*m_faces.size());

    int size = m_faces.size();

    for(int i=0 ; i < size ; ++i) {

        for(int j=0 ; j < 3 ; ++j) { m_vertices.push_back(new Vertex); }
        for(int j=0 ; j < 3 ; ++j) { m_faces.push_back(new Face); }
        for(int j=0 ; j < 9 ; ++j) { m_edges.push_back(new HalfEdge); }

        // Milieux des trois demi-arêtes de la face i
        m_vertices[m_vertices.size()-1]->index = m_vertices.size()-1;
        m_vertices[m_vertices.size()-2]->index = m_vertices.size()-2;
        m_vertices[m_vertices.size()-3]->index = m_vertices.size()-3;

        m_vertices[m_vertices.size()-1]->outgoing = m_edges[m_edges.size()-7];
        m_vertices[m_vertices.size()-2]->outgoing = m_edges[m_edges.size()-8];
        m_vertices[m_vertices.size()-3]->outgoing = m_edges[m_edges.size()-9];

        m_vertices[m_vertices.size()-1]->coords = (m_faces[i]->edge->vertex->coords + m_faces[i]->edge->previous->vertex->coords) / 2;
        m_vertices[m_vertices.size()-2]->coords = (m_faces[i]->edge->vertex->coords + m_faces[i]->edge->next->vertex->coords) / 2;
        m_vertices[m_vertices.size()-3]->coords = (m_faces[i]->edge->next->vertex->coords + m_faces[i]->edge->previous->vertex->coords) / 2;

        // Trois nouvelles faces créées
        m_faces[m_faces.size()-1]->edge = m_faces[i]->edge;
        m_faces[m_faces.size()-2]->edge = m_faces[i]->edge->next;
        m_faces[m_faces.size()-3]->edge = m_faces[i]->edge->previous;

        // Neuf nouvelles demi-arêtes créées
        m_edges[m_edges.size()-1]->face = m_faces[m_faces.size()-1];
        m_edges[m_edges.size()-2]->face = m_faces[m_faces.size()-1];
        m_edges[m_edges.size()-3]->face = m_faces[m_faces.size()-2];
        m_edges[m_edges.size()-4]->face = m_faces[m_faces.size()-2];
        m_edges[m_edges.size()-5]->face = m_faces[m_faces.size()-3];
        m_edges[m_edges.size()-6]->face = m_faces[m_faces.size()-3];
        m_edges[m_edges.size()-7]->face = m_faces[i];
        m_edges[m_edges.size()-8]->face = m_faces[i];
        m_edges[m_edges.size()-9]->face = m_faces[i];

        m_edges[m_edges.size()-1]->next = m_edges[m_edges.size()-2];
        m_edges[m_edges.size()-2]->next = m_faces[i]->edge;
        m_edges[m_edges.size()-3]->next = m_edges[m_edges.size()-4];
        m_edges[m_edges.size()-4]->next = m_faces[i]->edge->next;
        m_edges[m_edges.size()-5]->next = m_edges[m_edges.size()-6];
        m_edges[m_edges.size()-6]->next = m_faces[i]->edge->previous;
        m_edges[m_edges.size()-7]->next = m_edges[m_edges.size()-8];
        m_edges[m_edges.size()-8]->next = m_edges[m_edges.size()-9];
        m_edges[m_edges.size()-9]->next = m_edges[m_edges.size()-7];

        m_edges[m_edges.size()-1]->previous = m_faces[i]->edge;
        m_edges[m_edges.size()-2]->previous = m_edges[m_edges.size()-1];
        m_edges[m_edges.size()-3]->previous = m_faces[i]->edge->next;
        m_edges[m_edges.size()-4]->previous = m_edges[m_edges.size()-3];
        m_edges[m_edges.size()-5]->previous = m_faces[i]->edge->previous;
        m_edges[m_edges.size()-6]->previous = m_edges[m_edges.size()-5];
        m_edges[m_edges.size()-7]->previous = m_edges[m_edges.size()-9];
        m_edges[m_edges.size()-8]->previous = m_edges[m_edges.size()-7];
        m_edges[m_edges.size()-9]->previous = m_edges[m_edges.size()-8];

        m_edges[m_edges.size()-1]->opposite = m_faces[i]->edge->next->opposite;
        m_edges[m_edges.size()-2]->opposite = m_edges[m_edges.size()-7];
        m_edges[m_edges.size()-3]->opposite = m_faces[i]->edge->previous->opposite;
        m_edges[m_edges.size()-4]->opposite = m_edges[m_edges.size()-8];
        m_edges[m_edges.size()-5]->opposite = m_faces[i]->edge->opposite;
        m_edges[m_edges.size()-6]->opposite = m_edges[m_edges.size()-9];
        m_edges[m_edges.size()-7]->opposite = m_edges[m_edges.size()-2];
        m_edges[m_edges.size()-8]->opposite = m_edges[m_edges.size()-4];
        m_edges[m_edges.size()-9]->opposite = m_edges[m_edges.size()-6];

        m_edges[m_edges.size()-1]->vertex = m_vertices[m_vertices.size()-2];
        m_edges[m_edges.size()-2]->vertex = m_vertices[m_vertices.size()-1];
        m_edges[m_edges.size()-3]->vertex = m_vertices[m_vertices.size()-3];
        m_edges[m_edges.size()-4]->vertex = m_vertices[m_vertices.size()-2];
        m_edges[m_edges.size()-5]->vertex = m_vertices[m_vertices.size()-1];
        m_edges[m_edges.size()-6]->vertex = m_vertices[m_vertices.size()-3];
        m_edges[m_edges.size()-7]->vertex = m_vertices[m_vertices.size()-2];
        m_edges[m_edges.size()-8]->vertex = m_vertices[m_vertices.size()-3];
        m_edges[m_edges.size()-9]->vertex = m_vertices[m_vertices.size()-1];

        // Mise à jour des sommets de la face courante
        m_faces[i]->edge->vertex->outgoing = m_edges[m_edges.size()-1];
        m_faces[i]->edge->next->vertex->outgoing = m_edges[m_edges.size()-3];
        m_faces[i]->edge->previous->vertex->outgoing = m_edges[m_edges.size()-5];

        // Mise à jour des demi-arêtes de la face courante
        m_faces[i]->edge->previous->face = m_faces[m_faces.size()-3];
        m_faces[i]->edge->previous->next = m_edges[m_edges.size()-5];
        m_faces[i]->edge->previous->previous = m_edges[m_edges.size()-6];

        m_faces[i]->edge->next->face = m_faces[m_faces.size()-2];
        m_faces[i]->edge->next->next = m_edges[m_edges.size()-3];
        m_faces[i]->edge->next->previous = m_edges[m_edges.size()-4];

        m_faces[i]->edge->face = m_faces[m_faces.size()-1];
        m_faces[i]->edge->next = m_edges[m_edges.size()-1];
        m_faces[i]->edge->previous = m_edges[m_edges.size()-2];

        // Mise à jour des demi-arêtes opposées croisées
/*        if(m_faces[i]->edge->next->opposite->opposite == m_faces[i]->edge->next->opposite->previous->opposite->previous->opposite->previous->opposite) {
            m_faces[i]->edge->next->opposite->opposite = m_faces[i]->edge->next->previous->opposite->previous->opposite->previous;
            m_faces[i]->edge->next->opposite = m_faces[i]->edge->next->opposite->previous->opposite->previous->opposite->previous;
        }
/*
        if(m_faces[i]->edge->previous->opposite->opposite == m_faces[i]->edge->previous->opposite->previous->opposite->previous->opposite->previous->opposite) {
            m_faces[i]->edge->previous->opposite->opposite = m_faces[i]->edge->previous->previous->opposite->previous->opposite->previous;
            m_faces[i]->edge->previous->opposite = m_faces[i]->edge->previous->opposite->previous->opposite->previous->opposite->previous;
        }

        if(m_faces[i]->edge->opposite->opposite == m_faces[i]->edge->opposite->previous->opposite->previous->opposite->previous->opposite) {
            m_faces[i]->edge->opposite->opposite = m_faces[i]->edge->previous->opposite->previous->opposite->previous;
            m_faces[i]->edge->opposite = m_faces[i]->edge->opposite->previous->opposite->previous->opposite->previous;
        }
*/
        // Mise à jour de la face i
        m_faces[i]->edge = m_edges[m_edges.size()-7];
    }

    TEST();
    convertToBuffer();
    update();
}

void Model::decimate()
{

    convertToBuffer();
    update();
}

void Model::scale(float percent)
{
    QVector3D vertice;
    for(int i=0 ; i < m_vertices.size() ; ++i) {
        vertice = m_coords[i];
        vertice.setX((vertice.x()-getCenter().x())*percent + getCenter().x());
        vertice.setY((vertice.y()-getCenter().y())*percent + getCenter().y());
        vertice.setZ((vertice.z()-getCenter().z())*percent + getCenter().z());

        m_coords[i] = vertice;
        m_vertices[i]->coords = vertice;
    }
    update();
}

void Model::setWidth(float width){}
void Model::setHeight(float height){}
void Model::setDepth(float depth){}

void Model::paintGL()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    m_vertexbuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    m_vertexbuffer.release();

    m_indicebuffer.bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    m_indicebuffer.release();

    glDisableClientState(GL_VERTEX_ARRAY);
}

void Model::TEST() const
{
    qDebug() << "TEST of model" << getName();

    bool test = true;
    int errors = 0;

    for(int i=0 ; i < m_faces.size() ; ++i) {
        if(m_faces[i]->edge == NULL) {
            qDebug() << "Face" << i << "'s edge is NULL.";
            test = false;
            ++errors;
        }
    }

    for(int i=0 ; i < m_vertices.size() ; ++i) {
        if(m_vertices[i]->index != i) {
            qDebug() << "Vertex" << i << "'s index isn't correct.";
            test = false;
            ++errors;
        }
        if(m_vertices[i]->outgoing == NULL) {
            qDebug() << "Vertex" << i << "'s outgoing is NULL.";
            test = false;
            ++errors;
        }
    }

    for(int i=0 ; i < m_edges.size() ; ++i) {
        if(m_edges[i]->face == NULL) {
            qDebug() << "Edge" << i << "'s face is NULL.";
            test = false;
            ++errors;
        }
        if(m_edges[i]->next == NULL) {
            qDebug() << "Edge" << i << "'s next is NULL.";
            test = false;
            ++errors;
        }
        if(m_edges[i]->previous == NULL) {
            qDebug() << "Edge" << i << "'s previous is NULL.";
            test = false;
            ++errors;
        }
        if(m_edges[i]->opposite == NULL) {
            qDebug() << "Edge" << i << "'s opposite is NULL.";
            test = false;
            ++errors;
        }
        if(m_edges[i]->vertex == NULL) {
            qDebug() << "Edge" << i << "'s vertex is NULL.";
            test = false;
            ++errors;
        }
    }

    if(test) {
        for(int i=0 ; i < m_faces.size() ; ++i) {
            if(m_faces[i]->edge->face != m_faces[i]) {
                qDebug() << "Face" << i << "'s edge do not refer to the face.";
                test = false;
                ++errors;
            }
            if(m_faces[i]->edge->next->face != m_faces[i]) {
                qDebug() << "Face" << i << "'s edge's next do not refer to the face.";
                test = false;
                ++errors;
            }
            if(m_faces[i]->edge->previous->face != m_faces[i]) {
                qDebug() << "Face" << i << "'s edge's previous do not refer to the face.";
                test = false;
                ++errors;
            }
        }

        for(int i=0 ; i < m_vertices.size() ; ++i) {
            if(m_vertices[i]->outgoing->previous->vertex != m_vertices[i]) {
                qDebug() << "Vertex" << i << "'s outgoing's previous do not refer to the vertex.";
                test = false;
                ++errors;
            }
        }

        for(int i=0 ; i < m_edges.size() ; ++i) {
            if(m_edges[i] != m_edges[i]->next->previous) {
                qDebug() << "Edge" << i << "'s next's previous do not refer to the edge.";
                test = false;
                ++errors;
            }
            if(m_edges[i] != m_edges[i]->previous->next) {
                qDebug() << "Edge" << i << "'s previous's next do not refer to the edge.";
                test = false;
                ++errors;
            }
            if(m_edges[i] != m_edges[i]->opposite->opposite) {
                qDebug() << "Edge" << i << "'s opposite's opposite do not refer to the edge.";
                test = false;
                ++errors;
            }
        }
    }

    qDebug() << "TEST of model" << getName() << ":" << errors << "errors.";
}

/** Revoir les cours sur les héritages (L3 !!!!)*/
float Model::getHeight() const {}

float Model::getDepth() const {}

float Model::getWidth() const {}
