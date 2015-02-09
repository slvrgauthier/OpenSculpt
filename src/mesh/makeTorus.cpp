#include "Mesh.h"

void Mesh::makeTorus(float radiusH, float radiusV, int discretization) {
    this->clear();

    // Test de création d'un fan complet
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

    TEST();
}
