#include "Mesh.h"

void Mesh::makeTorus(float radiusH, float radiusV) {
    this->clear();

    QVector<QVector3D> face;
    face.push_back(QVector3D(0, 0, 0));
    face.push_back(QVector3D(1, 0, 0));
    face.push_back(QVector3D(.75, .75, 0));
    face.push_back(QVector3D(0, 1, 0));
    face.push_back(QVector3D(-.75, .75, 0));
    face.push_back(QVector3D(-1, 0, 0));
    face.push_back(QVector3D(-.75, -.75, 0));
    face.push_back(QVector3D(0, -1, 0));
    face.push_back(QVector3D(.75, -.75, 0));
    face.push_back(QVector3D(1, 0, 0));
    this->addFace(face);
/*
    QVector<QVector3D> face2;
    face2.push_back(QVector3D(2, 0, 0));
    face2.push_back(QVector3D(3, 0, 0));
    face2.push_back(QVector3D(2.5, 1, 0));

    this->addFace(face2);
*/
    TEST();
}
