#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector3D>
#include <QString>
#include "HalfEdge.h"

class Mesh {

public:
    Mesh();
    ~Mesh();

public:
    void makeCone(float height, float radiusUp, float radiusDown);
    void makeCube(float width, float height, float depth);
    void makeCylinder(float height, float radius);
    void makeSphere(float radius);
    void makeTorus(float radiusH, float radiusV);

private:
    void clear();

public:
    QString getName() const;
    void setName(QString name);

    QVector3D getCenter() const;
    void setCenter(QVector3D center);

    HalfEdge* getEdge(int index) const;
    void setEdge(int index, HalfEdge *edge);

    Vertex* getVertex(int index) const;
    void setVertex(int index, Vertex *vertex);

    Face* getFace(int index) const;
    void setFace(int index, Face *face);

    int getEdgeCount() const;
    int getVertexCount() const;
    int getFaceCount() const;

public:
    void TEST() const;

private:
    // Mesh infos
    QString m_name;
    QVector3D m_center;

    // 3D mesh
    QVector<HalfEdge*> m_edges;
    QVector<Vertex*> m_vertices;
    QVector<Face*> m_faces;
};

#endif // MESH_H
