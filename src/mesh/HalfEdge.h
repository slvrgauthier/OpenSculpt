#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <QVector3D>

struct HalfEdge;
struct Vertex;
struct Face;

typedef struct HalfEdge {
    Vertex* vertex;
    Face* face;
    HalfEdge* next;
    HalfEdge* opposite;
    HalfEdge* previous;
} HalfEdge;

typedef struct Vertex {
    QVector3D coords;
    HalfEdge* outgoing;
    int index;
} Vertex;

typedef struct Face {
    HalfEdge* edge;
} Face;

#endif // HALFEDGE_H
