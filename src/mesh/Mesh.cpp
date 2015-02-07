#include "Mesh.h"

Mesh::Mesh() { m_center = QVector3D(0.,0.,0.); }
Mesh::~Mesh() { this->clear(); }

void addFace(QVector<QVector3D> vertices) { /* TODO */ }
QVector3D cutEdge(QVector3D vertex1, QVector3D vertex2) { /* TODO */ }

QString Mesh::getName() const { return m_name; }
void Mesh::setName(QString name) { m_name = name; }

QVector3D Mesh::getCenter() const { return m_center; }
void Mesh::setCenter(QVector3D center) { m_center = center; }

HalfEdge* Mesh::getEdge(int index) const { return m_edges.at(index); }
void Mesh::setEdge(int index, HalfEdge *edge) { m_edges.replace(index, edge); }

Vertex* Mesh::getVertex(int index) const { return m_vertices.at(index); }
void Mesh::setVertex(int index, Vertex *vertex) { m_vertices.replace(index, vertex); }

Face* Mesh::getFace(int index) const { return m_faces.at(index); }
void Mesh::setFace(int index, Face *face) { m_faces.replace(index, face); }

int Mesh::getEdgeCount() const { return m_edges.size(); }
int Mesh::getVertexCount() const { return m_vertices.size(); }
int Mesh::getFaceCount() const { return m_faces.size(); }

void Mesh::resizeEdge(int count) {
    if(count < m_edges.size()) {
        for(int i=count ; i < m_edges.size() ; ++i) {
            delete m_edges[i];
        }
    }
    m_edges.resize(count);
}

void Mesh::resizeVertex(int count) {
    if(count < m_vertices.size()) {
        for(int i=count ; i < m_vertices.size() ; ++i) {
            delete m_vertices[i];
        }
    }
    m_vertices.resize(count);
}

void Mesh::resizeFace(int count) {
    if(count < m_faces.size()) {
        for(int i=count ; i < m_faces.size() ; ++i) {
            delete m_faces[i];
        }
    }
    m_faces.resize(count);
}

void Mesh::addEdge(HalfEdge *edge) { m_edges.push_back(edge); }
void Mesh::addVertex(Vertex *vertex) { m_vertices.push_back(vertex); }
void Mesh::addFace(Face *face) { m_faces.push_back(face); }

void Mesh::removeEdge(int index) { delete m_edges[index]; m_edges.remove(index); }
void Mesh::removeVertex(int index) { delete m_vertices[index]; m_vertices.remove(index); }
void Mesh::removeFace(int index) { delete m_faces[index]; m_faces.remove(index); }

void Mesh::clear() {
    for(int i=0 ; i < m_edges.size() ; ++i) {
        delete m_edges[i];
    }
    m_edges.clear();
    for(int i=0 ; i < m_vertices.size() ; ++i) {
        delete m_vertices[i];
    }
    m_vertices.clear();
    for(int i=0 ; i < m_faces.size() ; ++i) {
        delete m_faces[i];
    }
    m_faces.clear();
}

void Mesh::TEST() const {
    bool test = true;
    int errors = 0;

    for(int i=0 ; i < m_faces.size() ; ++i) {
        if(m_faces[i]->edge == NULL) {
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
            for(int j=i+1 ; j < m_vertices.size() ; ++j) {
                if(i != j && m_vertices[i]->coords == m_vertices[j]->coords) {
                    qDebug() << "Vertex" << i << "and Vertex" << j << "have equal coords.";
                    test = false;
                    ++errors;
                }
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

    qDebug() << "Integrity TEST of model" << getName() << ":" << errors << "errors.";
}
