/*
 * MeshRenderer.h
 * @author : Team OpenSculpt
 *
 * This file gives the declaration of the class MeshRenderer.
 * A MeshRenderer is an object dedicated to the Mesh rendering.
 *
 * MeshRenderer use buffer objects to significantly improve performances.
 *
 */

#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <QGLBuffer>
#include "Mesh.h"

class MeshRenderer {

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    MeshRenderer(Mesh *mesh);
    ~MeshRenderer();
    // =========================================================


    // ================== PUBLIC MEMBERS ==================
public:
    void paintGL();
    void update(); // Synchronise Mesh and buffer objects
    // ====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    Mesh* getMesh() const;
    // ======================================================


    // ================== PROPERTIES ==================
private:
    Mesh *m_mesh;

    // Rendering
    QVector<QVector3D> m_coords;
    QVector<GLuint> m_indices;

    // GPU Buffer
    QGLBuffer *m_vertexbuffer;
    QGLBuffer *m_indicebuffer;
};

#endif // MESHRENDERER_H
