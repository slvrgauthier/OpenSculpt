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
    friend class MeshRenderer;
    friend class MeshProcessing;

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    Mesh();
    ~Mesh();
    // Create a Mesh by copy
    static Mesh* copyMesh(Mesh *mesh);

    // Generate many predefined 3D polygons (extensible by developers)
    void makeCone(float height, float radiusUp, float radiusDown, int discretization);
    void makeCube(float width, float height, float depth, int discretization);
    void makeCylinder(float height, float radius, int discretization);
    void makeSphere(float radius, int discretization);
    void makeTorus(float radiusH, float radiusV, int discretization);
    // =========================================================


    // ================== PUBLIC MEMBERS (high level) ==================
public:
    // Add a face with triangles fan wich begins in vertices[0], vertices must be given in counterclockwise direction
    void addFace(QVector<QVector3D> vertices);

    // Cut an edge between two vertices in two parts equally
    void cutEdge(QVector3D vertex1, QVector3D vertex2);

    // Merge the two edges vertex1-to-vertex2 and vertex2-to-vertex3
    void mergeEdge(QVector3D vertex1, QVector3D vertex2, QVector3D vertex3);

    // Get a list of vertices in area "areaSize" around "position"
    QVector<QVector3D> getVertices(QVector3D position, float areaSize);

    // Get a list of vertices neighbours of "vertex" with "degree" recursions around
    QVector<QVector3D> getNeighbours(QVector3D vertex, int degree);

    // Get the normal of the face containing position
    QVector3D getNormal(QVector3D position);

    // Move a vertex or many vertices by "move"
    void moveVertex(QVector3D vertex, QVector3D move);
    void moveVertex(int index, QVector3D move);
    void moveVertices(QVector<QVector3D> vertices, QVector3D move);
    // =================================================================


    // ================== PRIVATE MEMBERS ==================
private:
    void getVerticesRec(QVector<QVector3D> &vertices, QVector3D position, float areaSize, HalfEdge *edge);
    void getNeighboursRec(QVector<QVector3D> &vertices, Vertex *v, int degree);
    void clear();
    void TEST() const;
    // =====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    QString getName() const;
    void setName(QString name);

    QVector3D getCenter() const;
    void setCenter(QVector3D center);

    QVector3D getCoords(int index) const;

    void setCoords(QVector3D vertex, QVector3D coord);
    void setCoords(int index, QVector3D coord);

    int getEdgeCount() const;
    int getVertexCount() const;
    int getFaceCount() const;
    // ======================================================


    // ================== PRIVATE ACCESSORS (low level) ==================
private:
    HalfEdge* getEdge(int index) const;
    void setEdge(int index, HalfEdge *edge);

    Vertex* getVertex(int index) const;
    void setVertex(int index, Vertex *vertex);

    Face* getFace(int index) const;
    void setFace(int index, Face *face);

    void resizeEdge(int count);
    void resizeVertex(int count);
    void resizeFace(int count);

    void addEdge(HalfEdge *edge);
    void addVertex(Vertex *vertex);
    void addFace(Face *face);

    void removeEdge(HalfEdge *edge);
    void removeVertex(Vertex *vertex);
    void removeFace(Face *face);

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
