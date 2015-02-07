/*
 * MeshManager.h
 * @author : Team OpenSculpt
 *
 * This file gives the declaration of the class MeshManager.
 * A MeshManager is a container
 *
 */

#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <QVector>
#include "MeshRenderer.h"

class MeshManager {

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    MeshManager();
    ~MeshManager();
    // =========================================================


    // ================== PUBLIC MEMBERS ==================
public:
    void paintGL();

    void addMesh(Mesh *mesh);
    void removeMesh();
    void clear();
    // ====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    Mesh* getMesh(int index);
    // ======================================================


    // ================== PROPERTIES ==================
private:
    QVector<MeshRenderer*> m_renderers;
};

#endif // MESHMANAGER_H
