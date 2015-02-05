/*
 * Model.h
 * @author : Team OpenSculpt
 *
 * Node represent a node of our internal mesh, with 3D position and neighbourhood.
 * Model is a mesh defined by a list of Nodes and let the user create base meshes.
 *
 * Models must be added to a ModelManager to be rendered.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QVector>
#include <QtGui/QVector3D>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>
#include <QString>
#include "model/halfedge.h"

using namespace std;

class Model
{
public:
    Model();
    ~Model();

public:
    virtual void initializeGL() = 0;
    virtual void paintGL();

    void convertToBuffer();
    void update();

public:
    virtual void subdivide();
    virtual void decimate();

    virtual void scale(float percent);

    virtual void setWidth(float width);
    virtual void setHeight(float height);
    virtual void setDepth(float depth);
    
public:
    QString getName() const;
    void setName(QString name);
    QVector3D getVertex(int index) const;
    void setVertex(int index, QVector3D vertex);
    QVector3D getCenter() const;
    void setCenter(QVector3D center);
    int getSize() const;

public:
    int closestVertex(QVector3D position) const;
    void TEST() const;

protected:
    // Model infos
    QString m_name;
    QVector3D m_center;

    // 3D mesh
    QVector<HalfEdge*> m_edges;
    QVector<Vertex*> m_vertices;
    QVector<Face*> m_faces;

    // Rendering
    QVector<QVector3D> m_coords;
    QVector<GLuint> m_indices;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;
    QGLBuffer m_indicebuffer;
};

#endif // MODEL_H
