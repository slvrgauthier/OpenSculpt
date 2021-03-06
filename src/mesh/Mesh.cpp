#include "Mesh.h"

Mesh::Mesh() { m_center = QVector3D(0.,0.,0.); }
Mesh::~Mesh() { this->clear(); }

/*Mesh *Mesh::copyMesh(Mesh *mesh) {
    Mesh *result = new Mesh();

    // Create Vertices
    result->resizeVertex(mesh->getVertexCount());
    Vertex *vertex;
    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        vertex = new Vertex;
        vertex->coords = mesh->getVertex(i)->coords;
        vertex->index = mesh->getVertex(i)->index;
        result->setVertex(i, vertex);
    }

    // Create Faces
    result->resizeFace(mesh->getFaceCount());
    Face *face;
    for(int i=0 ; i < mesh->getFaceCount() ; ++i) {
        face = new Face;
        result->setFace(i, face);
    }

    // Create Edges
    result->resizeEdge(mesh->getEdgeCount());
    HalfEdge *edge;
    for(int i=0 ; i < mesh->getEdgeCount() ; ++i) {
        edge = new HalfEdge;
        result->setEdge(i, edge);
    }

    // Fill Vertices
    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        vertex = result->getVertex(i);
        // need indices of edges and faces
    }

    // Fill Faces
    for(int i=0 ; i < mesh->getFaceCount() ; ++i) {
        face = result->getFace(i);
        // need indices of edges and faces
    }

    // Fill Edges
    for(int i=0 ; i < mesh->getEdgeCount() ; ++i) {
        edge = result->getEdge(i);
        // need indices of edges and faces
    }
}*/

bool Mesh::addFace(QVector<QVector3D> vertices) {
    int size = vertices.size();

    if(size >= 3) {
        // Merge with existing vertices
        QVector<Vertex*> tmp_vertices;
        tmp_vertices.resize(size);

        for(int i=0 ; i < tmp_vertices.size() ; ++i) {
            for(int v=0 ; v < getVertexCount() ; ++v) {
                if(m_vertices[v]->coords == vertices[i]) {
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

        for(int i=0 ; i < tmp_vertices.size() ; ++i) {
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
            tmp_edges[i]->opposite = tmp_edges[i];
        }

        // Link opposite edges
        for(int i=0 ; i < tmp_edges.size() ; ++i) {
            if(tmp_edges[i]->opposite == tmp_edges[i]) {
                for(int e=0 ; e < getEdgeCount() ; ++e) {
                    if(m_edges[e]->previous->vertex == tmp_edges[i]->vertex && m_edges[e]->vertex == tmp_edges[i]->previous->vertex) {
                        tmp_edges[i]->opposite = m_edges[e];
                        m_edges[e]->opposite = tmp_edges[i];
                    }
                }
            }
        }
        return true;
    }
    else {
        qDebug() << "A face needs at least three vertices";
        return false;
    }
}

bool Mesh::cutEdge(QVector3D vertex1, QVector3D vertex2) {
    if(vertex1 != vertex2) {

        HalfEdge *edge = NULL;

        int i=0;
        while(i < getEdgeCount()) {
            if(m_edges[i]->vertex->coords == vertex2 && m_edges[i]->previous->vertex->coords == vertex1) {
                edge = m_edges[i];
                i = getEdgeCount();
            }
            ++i;
        }

        if(edge != NULL) {
            // Create and fill new vertex
            Vertex *tmp_vertex = new Vertex;
            tmp_vertex->index = getVertexCount();
            tmp_vertex->coords = (vertex1 + vertex2) / 2.;
            tmp_vertex->outgoing = edge;

            m_vertices.push_back(tmp_vertex);

            // Create new edges
            QVector<HalfEdge*> tmp_edges;
            tmp_edges.resize(6);

            for(int i=0 ; i < tmp_edges.size() ; ++i) {
                tmp_edges[i] = new HalfEdge;
                m_edges.push_back(tmp_edges[i]);
            }

            // Create and fill new faces
            QVector<Face*> tmp_faces;
            tmp_faces.resize(4);

            tmp_faces[0] = edge->face;
            tmp_faces[0]->edge = edge;

            tmp_faces[1] = new Face; m_faces.push_back(tmp_faces[1]);
            tmp_faces[1]->edge = tmp_edges[2];

            tmp_faces[2] = new Face; m_faces.push_back(tmp_faces[2]);
            tmp_faces[2]->edge = tmp_edges[3];

            tmp_faces[3] = edge->opposite->face;
            tmp_faces[3]->edge = edge->opposite;

            // Fill new edges
            for(int i=0 ; i < tmp_edges.size() ; ++i) {
                tmp_edges[i]->face = tmp_faces[(i+1)/2];
                tmp_edges[i]->opposite = (i%2 == 0)? tmp_edges[i+1] : tmp_edges[i-1];
            }

            tmp_edges[0]->next = edge;
            tmp_edges[0]->previous = edge->next;
            tmp_edges[0]->vertex = tmp_vertex;

            tmp_edges[1]->next = edge->previous;
            tmp_edges[1]->previous = tmp_edges[2];
            tmp_edges[1]->vertex = edge->next->vertex;

            tmp_edges[2]->next = tmp_edges[1];
            tmp_edges[2]->previous = edge->previous;
            tmp_edges[2]->vertex = tmp_vertex;

            tmp_edges[3]->next = edge->opposite->next;
            tmp_edges[3]->previous = tmp_edges[4];
            tmp_edges[3]->vertex = edge->previous->vertex;

            tmp_edges[4]->next = tmp_edges[3];
            tmp_edges[4]->previous = edge->opposite->next;
            tmp_edges[4]->vertex = tmp_vertex;

            tmp_edges[5]->next = edge->opposite->previous;
            tmp_edges[5]->previous = edge->opposite;
            tmp_edges[5]->vertex = edge->opposite->next->vertex;

            // Fill old edges
            edge->next->face = tmp_faces[0];
            edge->next->next = tmp_edges[0];
            edge->next->previous = edge;

            edge->previous->face = tmp_faces[1];
            edge->previous->next = tmp_edges[2];
            edge->previous->previous = tmp_edges[1];

            edge->opposite->next->face = tmp_faces[2];
            edge->opposite->next->next = tmp_edges[4];
            edge->opposite->next->previous = tmp_edges[3];

            edge->opposite->previous->face = tmp_faces[3];
            edge->opposite->previous->next = edge->opposite;
            edge->opposite->previous->previous = tmp_edges[5];

            edge->opposite->face = tmp_faces[3];
            edge->opposite->next = tmp_edges[5];
            edge->opposite->previous = edge->opposite->previous;
            edge->opposite->vertex = tmp_vertex;

            edge->face = tmp_faces[0];
            edge->next = edge->next;
            edge->previous = tmp_edges[0];

            // Fill old vertex
            tmp_edges[3]->vertex->outgoing = tmp_edges[2];

            return true;
        }
        else {
            //qDebug() << "Cannot cut an edge wich does not exist";
            return false;
        }
    }
    else {
        //qDebug() << "Cannot cut an edge between clones of a vertex";
        return false;
    }
}

bool Mesh::mergeEdge(QVector3D vertex1, QVector3D vertex2, QVector3D vertex3) {
    if(vertex1 != vertex2 && vertex2 != vertex3 && vertex3 != vertex1 && !getNeighbours(vertex1, 1).contains(vertex3)) {

        HalfEdge *edge1 = NULL, *edge2 = NULL;

        int i=0;
        while(i < getEdgeCount()) {
            if(m_edges[i]->vertex->coords == vertex2 && m_edges[i]->previous->vertex->coords == vertex1) {
                edge1 = m_edges[i];
                if(edge2 != NULL) {
                    i = getEdgeCount();
                }
            }
            else if(m_edges[i]->vertex->coords == vertex3 && m_edges[i]->previous->vertex->coords == vertex2) {
                edge2 = m_edges[i];
                if(edge1 != NULL) {
                    i = getEdgeCount();
                }
            }
            ++i;
        }

        if(edge1 != NULL && edge2 != NULL && edge1->face != edge1->opposite->face) {
            // Fill and Remove faces
            edge1->next->opposite->face->edge = edge1->next->opposite->next;
            edge1->opposite->previous->opposite->face->edge = edge1->opposite->previous->opposite->previous;
            removeFace(edge1->opposite->face);
            removeFace(edge1->face);

            // Fill and Remove edges
            edge1->previous->face = edge1->next->opposite->face;
            edge1->previous->next = edge1->next->opposite->next;
            edge1->previous->previous = edge1->previous->next->next;
            edge1->previous->previous->next = edge1->previous;
            edge1->previous->next->previous = edge1->previous;
            removeEdge(edge1->next->opposite);
            removeEdge(edge1->next);

            edge1->opposite->next->face = edge1->opposite->previous->opposite->face;
            edge1->opposite->next->previous = edge1->opposite->previous->opposite->previous;
            edge1->opposite->next->next = edge1->opposite->next->previous->previous;
            edge1->opposite->next->previous->next = edge1->opposite->next;
            edge1->opposite->next->next->previous = edge1->opposite->next;
            removeEdge(edge1->opposite->previous->opposite);
            removeEdge(edge1->opposite->previous);

            // Fill and Remove vertices
            edge1->previous->previous->vertex->outgoing = edge1->previous;
            edge1->opposite->vertex->outgoing = edge2;
            edge1->opposite->next->vertex->outgoing = edge1->opposite->next->next;
            removeVertex(edge1->vertex);

            // Link edges with vertex1
            HalfEdge *tmp_edge = edge1->opposite->next->previous;
            do {
                tmp_edge->vertex = edge1->opposite->vertex;
                tmp_edge = tmp_edge->opposite->previous;
            } while(tmp_edge != edge1->previous);
            removeEdge(edge1->opposite);
            removeEdge(edge1);

            return true;
        }
        else {
            //qDebug() << "Cannot merge edges";
            return false;
        }
    }
    else {
        //qDebug() << "Cannot merge edges between clones of vertex";
        return false;
    }
}

QVector<QVector3D> Mesh::getVertices(QVector3D position, float areaSize) {

    Face *face = NULL;
    float distance;
    QVector3D p0, p1, p2;

    int i=0;
    while(i < getFaceCount()) {
        p0 = getFace(i)->edge->previous->vertex->coords;
        p1 = getFace(i)->edge->vertex->coords;
        p2 = getFace(i)->edge->next->vertex->coords;
        distance = position.distanceToPlane(p0, p1, p2);

        if(distance > -0.1 && distance < 0.1 && inTriangle(position, p0, p1, p2)) {
            face = getFace(i);
            i = getFaceCount();
        }
        ++i;
    }

    QVector<QVector3D> vertices;
    if(face != NULL) {
        vertices.push_back(p0);
        vertices.push_back(p1);
        vertices.push_back(p2);

        if(areaSize > 0) {
            getVerticesRec(vertices, position, areaSize, face->edge->previous->opposite);
            getVerticesRec(vertices, position, areaSize, face->edge->opposite);
            getVerticesRec(vertices, position, areaSize, face->edge->next->opposite);
        }
    }

    return vertices;
}

QVector<QVector3D> Mesh::getNeighbours(QVector3D vertex, int degree) {

    Vertex *v = NULL;

    int i=0;
    while(i < getVertexCount()) {
        if(getVertex(i)->coords == vertex) {
            v = getVertex(i);
            i = getVertexCount();
        }
        ++i;
    }

    QVector<QVector3D> vertices;
    if(v != NULL) {
        getNeighboursRec(vertices, v, degree);
    }

    return vertices;
}

QVector3D Mesh::getNormal(QVector3D position) {
    QVector<QVector3D> vertices = getVertices(position, 0);
    if(vertices.size() >= 3) {
        return QVector3D::normal(vertices[0], vertices[1], vertices[2]).normalized();
    }
    else {
        return (position-getCenter()).normalized();
    }
}

void Mesh::moveVertex(QVector3D vertex, QVector3D move) {
    for(int i=0 ; i < getVertexCount() ; ++i) {
        if(m_vertices[i]->coords == vertex) {
            m_vertices[i]->coords += move;
        }
    }
}

void Mesh::moveVertex(int index, QVector3D move) {
    if(index >= 0 && index < getVertexCount()) {
        m_vertices[index]->coords += move;
    }
}

void Mesh::moveVertices(QVector<QVector3D> vertices, QVector3D move) {
    for(int i=0 ; i < getVertexCount() ; ++i) {
        for(int j=0 ; j < vertices.size() ; ++j) {
            if(m_vertices[i]->coords == vertices[j]) {
                m_vertices[i]->coords += move;
            }
        }
    }
}

QString Mesh::getName() const { return m_name; }
void Mesh::setName(QString name) { m_name = name; }

QVector3D Mesh::getCenter() const { return m_center; }
void Mesh::setCenter(QVector3D center) { m_center = center; }

QVector3D Mesh::getCoords(int index) const {
    if(index >= 0 && index < getVertexCount()) {
        return m_vertices[index]->coords;
    }
    else {
        return QVector3D();
    }
}

void Mesh::setCoords(QVector3D vertex, QVector3D coord) {
    for(int i=0 ; i < getVertexCount() ; ++i) {
        if(m_vertices[i]->coords == vertex) {
            m_vertices[i]->coords = coord;
        }
    }
}

void Mesh::setCoords(int index, QVector3D coord) {
    if(index >= 0 && index < getVertexCount()) {
        m_vertices[index]->coords = coord;
    }
}

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

void Mesh::removeEdge(HalfEdge *edge) { delete edge; m_edges.remove(m_edges.indexOf(edge)); }
void Mesh::removeVertex(Vertex *vertex) {
    for(int i=vertex->index+1 ; i < getVertexCount() ; ++i) {
        --m_vertices[i]->index;
    }
    m_vertices.remove(vertex->index);
    delete vertex;
}
void Mesh::removeFace(Face *face) { delete face; m_faces.remove(m_faces.indexOf(face)); }

void Mesh::getVerticesRec(QVector<QVector3D> &vertices, QVector3D position, float areaSize, HalfEdge *edge) {
    QVector3D p = edge->next->vertex->coords;
    if(position.distanceToPoint(p) < areaSize && !vertices.contains(p)) {
        vertices.push_back(p);
        getVerticesRec(vertices, position, areaSize, edge->previous->opposite);
        getVerticesRec(vertices, position, areaSize, edge->next->opposite);
    }
}

void Mesh::getNeighboursRec(QVector<QVector3D> &vertices, Vertex *v, int degree) {
    if(!vertices.contains(v->coords)) {
        vertices.push_back(v->coords);

        if(degree > 0) {
            HalfEdge *edge = v->outgoing;
            do {
                getNeighboursRec(vertices, edge->vertex, degree - 1);
                edge = edge->opposite->next;
            } while(edge != v->outgoing);
        }
    }
}

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
            if(m_edges[i]->opposite == m_edges[i]) {
                qDebug() << "Edge" << i << "'s opposite is itself.";
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
