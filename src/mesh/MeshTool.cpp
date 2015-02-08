#include "MeshTool.h"


// GLOBAL TOOLS

void MeshTool::gtmove(Mesh *mesh, QVector3D move) {
    qDebug() << "GTMove action";

    QVector3D tmp_move = move;
    tmp_move.setZ(-move.z());

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->getVertex(i)->coords += tmp_move;
    }

    mesh->setCenter(mesh->getCenter() + tmp_move);
}

void MeshTool::gtrotate(Mesh *mesh, QVector3D move) {
    qDebug() << "GTRotate action";

    QVector3D center = mesh->getCenter();
    QVector3D currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = mesh->getVertex(i)->coords - center;
        mesh->getVertex(i)->coords = rotateXYZ(currentPoint, move) + center;
    }
}

void MeshTool::gtscale(Mesh *mesh, QVector3D move) {
    qDebug() << "GTScale action";

    float coef = 1.0 - move.y() / 200.;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->getVertex(i)->coords = (mesh->getVertex(i)->coords - mesh->getCenter()) * coef + mesh->getCenter();
    }
}


// LOCAL TOOLS

void MeshTool::ltadd(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTAdd action";
    if(mesh==NULL&&last_position.x()==move.x()&&brushSize>0){}
}

void MeshTool::ltinflate(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTInflate action";
    if(mesh==NULL&&last_position.x()==move.x()&&brushSize>0){}
}

void MeshTool::ltmove(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTMove action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        Face *face = mesh->intersectedFace(position); // Face touchée par le rayon

        if(face != NULL) {
            Vertex *vertex = face->edge->vertex;
            float coef = std::max(0.f, 1 - vertex->coords.distanceToPoint(position) / brushSize);
            vertex->coords = vertex->coords + move * coef;
            mesh->setVertex(vertex->index, vertex);

            vertex = face->edge->next->vertex;
            coef = std::max(0.f, 1 - vertex->coords.distanceToPoint(position) / brushSize);
            vertex->coords = vertex->coords + move * coef;
            mesh->setVertex(vertex->index, vertex);

            vertex = face->edge->previous->vertex;
            coef = std::max(0.f, 1 - vertex->coords.distanceToPoint(position) / brushSize);
            vertex->coords = vertex->coords + move * coef;
            mesh->setVertex(vertex->index, vertex);
        }
    }
}

void MeshTool::ltpinch(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTPinch action";
    if(mesh==NULL&&last_position.x()==move.x()&&brushSize>0){}
}

void MeshTool::ltsmooth(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTSmooth action";
    if(mesh==NULL&&last_position.x()==move.x()&&brushSize>0){}
}

