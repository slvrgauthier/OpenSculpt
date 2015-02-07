/*
 * MeshManager.h
 * @author : Team OpenSculpt
 *
 * This file gives the declaration of the class MeshManager.
 * A MeshManager is a container of MeshRenderers.
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
    void updateMesh(int index);
    void updateLastMesh();

    void addMesh(Mesh *mesh);
    void removeMesh(Mesh *mesh);
    void clear();
    // ====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    Mesh* getMesh(int index) const;
    int getSize() const;
    // ======================================================


    // ================== PROPERTIES ==================
private:
    QVector<MeshRenderer*> m_renderers;
};

#endif // MESHMANAGER_H
