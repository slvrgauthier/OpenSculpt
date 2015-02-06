#ifndef MESHPROCESSING_H
#define MESHPROCESSING_H

#include "Mesh.h"

class MeshProcessing {

public:
    MeshProcessing();
    ~MeshProcessing();

public:
    void subdivide(Mesh *mesh, float maxEdgeLength);
    void decimate(Mesh *mesh, float minEdgeLength);

    void scale(Mesh *mesh, QVector3D coef);

public:
    int closestVertex(Mesh *mesh, QVector3D position) const;
    Face* intersectedFace(Mesh *mesh, QVector3D position) const;
};

#endif // MESHPROCESSING_H
