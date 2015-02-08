#include "Mesh.h"

void Mesh::makeSphere(float radius) {
    this->clear();

    // Test de création d'un cube avec addFace

    QVector<QVector3D> face; // front
    face.push_back(QVector3D(-1, -1, 1));
    face.push_back(QVector3D(1, -1, 1));
    face.push_back(QVector3D(1, 1, 1));
    face.push_back(QVector3D(-1, 1, 1));

    this->addFace(face);

    face.clear(); // right
    face.push_back(QVector3D(1, -1, 1));
    face.push_back(QVector3D(1, -1, -1));
    face.push_back(QVector3D(1, 1, -1));
    face.push_back(QVector3D(1, 1, 1));

    this->addFace(face);

    face.clear(); // back
    face.push_back(QVector3D(1, -1, -1));
    face.push_back(QVector3D(-1, -1, -1));
    face.push_back(QVector3D(-1, 1, -1));
    face.push_back(QVector3D(1, 1, -1));

    this->addFace(face);

    face.clear(); // left
    face.push_back(QVector3D(-1, -1, -1));
    face.push_back(QVector3D(-1, -1, 1));
    face.push_back(QVector3D(-1, 1, 1));
    face.push_back(QVector3D(-1, 1, -1));

    this->addFace(face);

    face.clear(); // up
    face.push_back(QVector3D(-1, 1, 1));
    face.push_back(QVector3D(1, 1, 1));
    face.push_back(QVector3D(1, 1, -1));
    face.push_back(QVector3D(-1, 1, -1));

    this->addFace(face);

    face.clear(); // down
    face.push_back(QVector3D(-1, -1, -1));
    face.push_back(QVector3D(1, -1, -1));
    face.push_back(QVector3D(1, -1, 1));
    face.push_back(QVector3D(-1, -1, 1));

    this->addFace(face);

    TEST();
}
