/*
 * Mesh.h
 * @author : Team OpenSculpt
 *
 * This file gives the declaration of the class Mesh.
 * A Mesh defines the internal mesh used in the application and gives some predefined 3D meshes.
 *
 * Public members let developers to easily extend the predefined meshes list but with a lack of performances,
 * whereas private members let developers to have high performance but more difficulties to program.
 *
 */

#ifndef MESH_H
#define MESH_H

#include <QVector>
#include <QVector3D>
#include <QString>
#include "HalfEdge.h"
#include "functions.h"

#include <QDebug>

class Mesh {
public: // A ENLEVER...
    int closestVertex(QVector3D position) const;
    Face* intersectedFace(QVector3D position) const;

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    Mesh();
    ~Mesh();

    // Generate many polygons (extensible by developers)
    void makeCone(float height, float radiusUp, float radiusDown);
    void makeCube(float width, float height, float depth);
    void makeCylinder(float height, float radius);
    void makeSphere(float radius);
    void makeTorus(float radiusH, float radiusV);
    // =========================================================


    // ================== PUBLIC MEMBERS (high level) ==================
public:
    // Add a face with triangles fan wich begins in vertices[0], vertices must be given in counterclockwise direction
    void addFace(QVector<QVector3D> vertices);

    // Cut an edge between two vertices in two parts equally
    void cutEdge(QVector3D vertex1, QVector3D vertex2);
    // =================================================================


    // ================== PRIVATE MEMBERS ==================
private:
    void clear();
    void TEST() const;
    // =====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    QString getName() const;
    void setName(QString name);

    QVector3D getCenter() const;
    void setCenter(QVector3D center);
    // ======================================================


    // ================== PRIVATE ACCESSORS (low level) ==================
public: // -> private -> à remplacer par void moveVertex(...)
    HalfEdge* getEdge(int index) const;
    void setEdge(int index, HalfEdge *edge);

    Vertex* getVertex(int index) const;
    void setVertex(int index, Vertex *vertex);

    Face* getFace(int index) const;
    void setFace(int index, Face *face);

    int getEdgeCount() const;
    int getVertexCount() const;
    int getFaceCount() const;

    void resizeEdge(int count);
    void resizeVertex(int count);
    void resizeFace(int count);

    void addEdge(HalfEdge *edge);
    void addVertex(Vertex *vertex);
    void addFace(Face *face);

    void removeEdge(int index);
    void removeVertex(int index);
    void removeFace(int index);
    // ====================================================================


    // ================== PROPERTIES ==================
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
