#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include <QVector>
#include "Mesh.h"

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
    QVector<Mesh*> m_meshes;
};

#endif // MESHMANAGER_H
