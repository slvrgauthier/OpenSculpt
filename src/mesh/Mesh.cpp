#include "Mesh.h"

Mesh::Mesh() { m_center = QVector3D(0.,0.,0.); }
Mesh::~Mesh() { this->clear(); }

void Mesh::addFace(QVector<QVector3D> vertices) {
    int size = vertices.size();

    if(size >= 3) {
        // Merge with existing vertices
        QVector<Vertex*> tmp_vertices;
        tmp_vertices.resize(size);

        for(int i=0 ; i < tmp_vertices.size() ; ++i) {
            for(int v=0 ; v < getVertexCount() ; ++v) {
                if(m_vertices[v]->coords == vertices[v]) {
                    tmp_vertices[i] = m_vertices[v];
                }
            }
        }
        for(int i=0 ; i < size-1 ; ++i) {
            for(int j=i+1 ; j < size ; ++j) {
                if(vertices[i] == vertices[j]) {
                    tmp_vertices[j] = tmp_vertices[i];
                }
            }
        }

        // Merge with existing edges
        QVector<HalfEdge*> tmp_edges;
        tmp_edges.resize(3 * (size - 2));

        for(int i=0 ; i < tmp_edges.size() ; ++i) {
            for(int e=0 ; e < getEdgeCount() ; ++e) {
                if(m_edges[e]->previous->vertex->coords == vertices[i] && m_edges[e]->vertex->coords == vertices[(i+1)%size]) {
                    tmp_edges[i] = m_edges[e];
                }
            }
        }

        // Create new vertices
        for(int i=0 ; i < tmp_vertices.size() ; ++i) {
            if(tmp_vertices[i] == NULL) {
                tmp_vertices[i] = new Vertex;
                tmp_vertices[i]->index = getVertexCount();
                tmp_vertices[i]->coords = vertices[i];

                m_vertices.push_back(tmp_vertices[i]);

                // Avoid clones
                for(int j=i+1 ; j < tmp_vertices.size() ; ++j) {
                    if(vertices[i] == vertices[j]) {
                        tmp_vertices[j] = tmp_vertices[i];
                    }
                }
            }
        }

        // Create new edges
        for(int i=0 ; i < tmp_edges.size() ; ++i) {
            if(tmp_edges[i] == NULL) {
                tmp_edges[i] = new HalfEdge;
                m_edges.push_back(tmp_edges[i]);
            }
        }

        // Create and fill new faces
        QVector<Face*> tmp_faces;
        tmp_faces.resize(size - 2);
        for(int i=0 ; i < tmp_faces.size() ; ++i) {
            tmp_faces[i] = new Face;
            tmp_faces[i]->edge = tmp_edges[3 * i];

            m_faces.push_back(tmp_faces[i]);
        }

        // Fill new vertices
        tmp_vertices[0]->outgoing = tmp_edges[0];
        tmp_vertices[1]->outgoing = tmp_edges[1];
        for(int i=2 ; i < tmp_vertices.size()-1 ; ++i) {
            tmp_vertices[i]->outgoing = tmp_edges[3 * i - 2];
        }
        tmp_vertices[tmp_vertices.size()-1]->outgoing = tmp_edges[3 * (tmp_vertices.size()-1) - 4];

        // Fill new edges
        for(int i=0 ; i < tmp_edges.size() ; ++i) {
            tmp_edges[i]->face = tmp_faces[i/3];
            tmp_edges[i]->next = (i%3 == 2)? tmp_edges[i-2] : tmp_edges[i+1];
            tmp_edges[i]->previous = (i%3 == 0)? tmp_edges[i+2] : tmp_edges[i-1];
            tmp_edges[i]->vertex = (i%3 == 2)? tmp_vertices[0] : tmp_vertices[i/3 + i%3 + 1];
        }

        // Link opposite edges
        for(int i=0 ; i < tmp_edges.size() ; ++i) {
            if(tmp_edges[i]->opposite == NULL) {
                for(int e=0 ; e < getEdgeCount() ; ++e) {
                    if(m_edges[e]->previous->vertex == tmp_edges[i]->vertex && m_edges[e]->vertex == tmp_edges[i]->previous->vertex) {
                        tmp_edges[i]->opposite = m_edges[e];
                        m_edges[e]->opposite = tmp_edges[i];
                    }
                }
            }
        }
    }
    else {
        qDebug() << "A face needs at least three vertices";
    }
}

QVector3D Mesh::cutEdge(QVector3D vertex1, QVector3D vertex2) {
    /* TODO */
}

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


// A ENLEVER...
int Mesh::closestVertex(QVector3D position) const
{
    int index = 0;
    float distance = position.distanceToPoint(getVertex(0)->coords);

    float d;
    for(int i=1 ; i < getVertexCount() ; ++i) {
        d = position.distanceToPoint(getVertex(i)->coords);
        if(d < distance) {
            distance = d;
            index = i;
        }
    }

    return index;
}

Face* Mesh::intersectedFace(QVector3D position) const
{
    float distance;
    for(int i=0 ; i < getFaceCount() ; ++i) {
        distance = position.distanceToPlane(getFace(i)->edge->previous->vertex->coords,
                                            getFace(i)->edge->vertex->coords,
                                            getFace(i)->edge->next->vertex->coords);
        if(distance > -0.1 && distance < 0.1) {
            return getFace(i);
        }
    }

    return NULL;
}
