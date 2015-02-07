#include "Mesh.h"

void Mesh::makeSphere(float radius) {
    this->clear();

    QVector<QVector3D> face1;
    face1.push_back(QVector3D(-1, -1, -1));
    face1.push_back(QVector3D(1, -1, -1));
    face1.push_back(QVector3D(1, 1, -1));
    face1.push_back(QVector3D(-1, 1, -1));

    this->addFace(face1);

    QVector<QVector3D> face2;
    face2.push_back(QVector3D(1, -1, -1));
    face2.push_back(QVector3D(1, -1, 1));
    face2.push_back(QVector3D(1, 1, 1));
    face2.push_back(QVector3D(1, 1, -1));

    this->addFace(face2);

    QVector<QVector3D> face3;
    face3.push_back(QVector3D(1, -1, 1));
    face3.push_back(QVector3D(-1, -1, 1));
    face3.push_back(QVector3D(-1, 1, 1));
    face3.push_back(QVector3D(1, 1, 1));

    this->addFace(face3);

    QVector<QVector3D> face4;
    face4.push_back(QVector3D(-1, -1, 1));
    face4.push_back(QVector3D(-1, -1, -1));
    face4.push_back(QVector3D(-1, 1, -1));
    face4.push_back(QVector3D(-1, 1, 1));

    this->addFace(face4);

    QVector<QVector3D> face5;
    face5.push_back(QVector3D(-1, 1, -1));
    face5.push_back(QVector3D(1, 1, -1));
    face5.push_back(QVector3D(1, 1, 1));
    face5.push_back(QVector3D(-1, 1, 1));

    this->addFace(face5);

    QVector<QVector3D> face6;
    face6.push_back(QVector3D(-1, -1, 1));
    face6.push_back(QVector3D(1, -1, 1));
    face6.push_back(QVector3D(1, -1, -1));
    face6.push_back(QVector3D(-1, -1, -1));

    this->addFace(face6);
}
