#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <QVector>
#include "Mesh.h"
#include "MeshRenderer.h"

class MeshManager {

public:
    MeshManager();
    ~MeshManager();

public:
    void paintGL();

public:
    void addMesh(Mesh *mesh);
    void removeMesh();
    void clear();

    Mesh* getMesh(int index);

private:
    QVector<MeshRenderer*> m_renderers;

};

#endif // MESHMANAGER_H
