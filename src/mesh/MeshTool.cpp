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
    QVector3D normal = mesh->getNormal(position);

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], normal * coef / 2);
        }
    } // POURQUOI VOUS VOUS EMBETEZ A FAIRE COMPLIQUE QUAND JE VOUS DONNE TOUT CE QU'IL FAUT...
/*
    // QVector3D normal = mesh->getNormal(position);
    if(!position.isNull()) {
        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        //Trouver les trois points les plus proches de position
        QVector<float> distance;
        for(int i=0;i<vertices.size();i++){
            distance.push_back(position.distanceToPoint(vertices[i]));
        }
        float mindist1=distance[0];
        int index1=0;
        for(int i=0;i<distance.size();i++){
            if(distance[i]<mindist1)
            {
                mindist1=distance[i];
                index1=i;
            }
        }
        float mindist2=1./0.;
        int index2=-1;
        for(int i=0;i<distance.size();i++){
            if(index1!=index2 && index1!=i && distance[i]<mindist2)
            {
                mindist2=distance[i];
                index2=i;
            }
        }
        float mindist3=1./0.;
        int index3=-1;
        for(int i=0;i<distance.size();i++){
            if(index1!=index2 && index1!=i && index2!=index3 && index2!=i && distance[i]<mindist3)
            {
                mindist3=distance[i];
                index3=i;
            }
        }
        QVector<QVector3D> verticesFace;
        verticesFace.push_back(vertices[index1]);
        verticesFace.push_back(vertices[index2]);
        verticesFace.push_back(vertices[index3]);


        int indexFace=mesh->getIndexFace(verticesFace); //indice de la face

        QVector3D normalFace = QVector3D::normal(verticesFace[0],verticesFace[1],verticesFace[2]);

        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);

            mesh->moveVertex(vertices[i],normalFace *coef );

        }
    }//if position
    */
}

void MeshTool::ltinflate(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTInflate action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size() ; ++i) {

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

void MeshTool::ltpinch(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTPinch action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size() ; ++i) {

        }
    }
}

void MeshTool::ltsmooth(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    qDebug() << "LTSmooth action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size() ; ++i) {

        }
    }
}

