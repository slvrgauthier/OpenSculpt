#ifndef MESHPROCESSING_H
#define MESHPROCESSING_H

#include "Mesh.h"

class MeshProcessing {

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    MeshProcessing();
    ~MeshProcessing();
    // =========================================================


    // ================== PUBLIC MEMBERS ==================
public:
    // Subdivide or Decimate the entire Mesh
    void subdivide(Mesh *mesh);
    void decimate(Mesh *mesh);

    // Subdivide or Decimate only half-edges wich break the criterion
    void subdivideAuto(Mesh *mesh, float maxEdgeLength);
    void decimateAuto(Mesh *mesh, float minEdgeLength);

    // Scale the entire Mesh along the three axis separately
    void scale(Mesh *mesh, QVector3D coef);
    // ====================================================


    // ================== PRIVATE MEMBERS ==================
private:
    int closestVertex(Mesh *mesh, QVector3D position) const;
    Face* intersectedFace(Mesh *mesh, QVector3D position) const;
};

#endif // MESHPROCESSING_H
