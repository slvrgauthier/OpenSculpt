#include "MeshProcessing.h"

MeshProcessing::MeshProcessing() {  }
MeshProcessing::~MeshProcessing() {  }

void MeshProcessing::subdivide(Mesh *mesh, float maxEdgeLength) {  }
void MeshProcessing::decimate(Mesh *mesh, float minEdgeLength) {  }

void MeshProcessing::scale(Mesh *mesh, QVector3D coef) {
    Vertex *vertice;
    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        vertice = mesh->getVertex(i);
        vertice->coords = mesh->getVertex(i)->coords - mesh->getCenter()*coef + mesh->getCenter();
    }
}

int MeshProcessing::closestVertex(Mesh *mesh, QVector3D position) const
{
    int index = 0;
    float distance = position.distanceToPoint(mesh->getVertex(0)->coords);

    float d;
    for(int i=1 ; i < mesh->getVertexCount() ; ++i) {
        d = position.distanceToPoint(mesh->getVertex(i)->coords);
        if(d < distance) {
            distance = d;
            index = i;
        }
    }

    return index;
}

Face* MeshProcessing::intersectedFace(Mesh *mesh, QVector3D position) const
{
    float distance;
    for(int i=0 ; i < mesh->getFaceCount() ; ++i) {
        distance = position.distanceToPlane(mesh->getFace(i)->edge->previous->vertex->coords,
                                            mesh->getFace(i)->edge->vertex->coords,
                                            mesh->getFace(i)->edge->next->vertex->coords);
        if(distance > -0.1 && distance < 0.1) {
            return mesh->getFace(i);
        }
    }

    return NULL;
}
