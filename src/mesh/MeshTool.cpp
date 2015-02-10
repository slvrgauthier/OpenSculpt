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

    QVector3D center = mesh->getCenter();
    QVector3D currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = rotateXYZ(mesh->getCoords(i) - center, move);
        currentPoint.setZ(-currentPoint.z());
        mesh->setCoords(i, currentPoint + center);
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

void MeshTool::ltadd(Mesh *mesh, QPoint last_position, float brushSize, Qt::KeyboardModifiers modifiers) {
    qDebug() << "LTAdd action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size() ; ++i) {
            mesh->moveVertex(vertices[i], normal / 20.);
        }
    }
}

void MeshTool::ltinflate(Mesh *mesh, QPoint last_position, float brushSize, Qt::KeyboardModifiers modifiers) {
    qDebug() << "LTInflate action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;
        float dist;
        for(int i=0 ; i < vertices.size() ; ++i) {
          dist= vertices[i].distanceToPoint(position) * brushSize /100;

          coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
          coef = coef+ dist;
          mesh->moveVertex(vertices[i], normal * coef);
        }
    }
}

void MeshTool::ltmove(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTMove action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], move * coef);
        }
    }
}

void MeshTool::ltpinch(Mesh *mesh, QPoint last_position, float brushSize, Qt::KeyboardModifiers modifiers) {
    qDebug() << "LTPinch action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {

        }
    }
}

void MeshTool::ltsmooth(Mesh *mesh, QPoint last_position, float brushSize) {
    qDebug() << "LTSmooth action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {

        }
    }
}

// OTHERS

void MeshTool::subdivideAuto(Mesh *mesh, QPoint last_position, float brushSize, float maxEdgeLength) {
    qDebug() << "SubdivideAuto action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size()-1 ; ++i) {
            for(int j=i+1 ; j < vertices.size() ; ++j) {
                if(vertices[i].distanceToPoint(vertices[j]) > maxEdgeLength) {
                    mesh->cutEdge(vertices[i], vertices[j]);
                }
            }
        }
    }
}
