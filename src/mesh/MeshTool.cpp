#include "MeshTool.h"
#include "Mesh.h"

// GLOBAL TOOLS

void MeshTool::gtmove(Mesh *mesh, QVector3D move) {
    qDebug() << "GTMove action";

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->moveVertex(i ,move);
    }

    mesh->setCenter(mesh->getCenter() + move);
}

void MeshTool::gtrotate(Mesh *mesh, QVector3D move) {
    qDebug() << "GTRotate action";

    QVector3D tmp_move = move;
    tmp_move.setZ(-move.z());

    QVector3D center = mesh->getCenter();
    QVector3D currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = mesh->getCoords(i) - center;
        mesh->setCoords(i, rotateXYZ(currentPoint, tmp_move) + center);
    }
}

void MeshTool::gtscale(Mesh *mesh, QVector3D move) {
    qDebug() << "GTScale action";

    float coef = 1.0 - move.y() / 200.;
    QVector3D center = mesh->getCenter();

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->setCoords(i, (mesh->getCoords(i) - center) * coef + center);
    }
}


// LOCAL TOOLS

void MeshTool::ltadd(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTAdd action";
    QVector3D position = get3Dposition(last_position); // Position dans le repère scène
    //QVector3D normal = mesh->getNormal(position);

    QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
    float coef;

    for(int i=0 ; i < vertices.size() ; ++i) {
        coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);

        mesh->moveVertex(vertices[i], move  *coef);

    }

}

void MeshTool::ltinflate(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTInflate action";
    if(mesh==NULL&&last_position.x()==move.x()&&brushSize>0){}
}

void MeshTool::ltmove(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTMove action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], mesh->getNormal(position) * coef);
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

