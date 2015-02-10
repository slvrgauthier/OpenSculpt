#include "Mesh.h"

void Mesh::makeCube(float width, float height, float depth, int discretization) {
    this->clear();

    QVector<QVector3D> face;
    float w = width/2, h = height/2, d = depth/2;
    float sizeX, sizeY, sizeZ, x, y, z;

    sizeX = width / discretization;
    sizeY = height / discretization;
    sizeZ = depth / discretization;

    for(int i=0 ; i < discretization ; ++i) {
        for(int j=0 ; j < discretization ; ++j) {
            // Front and Back
            x = i * sizeX - w;
            y = j * sizeY - h;

            // Front
            face.clear();
            face.push_back(QVector3D(x, y, d));
            face.push_back(QVector3D(x + sizeX, y, d));
            face.push_back(QVector3D(x + sizeX, y + sizeY, d));
            face.push_back(QVector3D(x, y + sizeY, d));

            this->addFace(face);

            // Back
            face.clear();
            face.push_back(QVector3D(x + sizeX, y, -d));
            face.push_back(QVector3D(x, y, -d));
            face.push_back(QVector3D(x, y + sizeY, -d));
            face.push_back(QVector3D(x + sizeX, y + sizeY, -d));

            this->addFace(face);

            // Left and Right
            z = i * sizeZ - d;
            y = j * sizeY - h;

            // Left
            face.clear();
            face.push_back(QVector3D(-w, y, z));
            face.push_back(QVector3D(-w, y, z + sizeZ));
            face.push_back(QVector3D(-w, y + sizeY, z + sizeZ));
            face.push_back(QVector3D(-w, y + sizeY, z));

            this->addFace(face);

            // Right
            face.clear();
            face.push_back(QVector3D(w, y, z + sizeZ));
            face.push_back(QVector3D(w, y, z));
            face.push_back(QVector3D(w, y + sizeY, z));
            face.push_back(QVector3D(w, y + sizeY, z + sizeZ));

            this->addFace(face);

            // Up and Down
            x = i * sizeX - w;
            z = j * sizeZ - d;

            // Up
            face.clear();
            face.push_back(QVector3D(x, h, z + sizeZ));
            face.push_back(QVector3D(x + sizeX, h, z + sizeZ));
            face.push_back(QVector3D(x + sizeX, h, z));
            face.push_back(QVector3D(x, h, z));

            this->addFace(face);

            // Down
            face.clear();
            face.push_back(QVector3D(x, -h, z));
            face.push_back(QVector3D(x + sizeX, -h, z));
            face.push_back(QVector3D(x + sizeX, -h, z + sizeZ));
            face.push_back(QVector3D(x, -h, z + sizeZ));

            this->addFace(face);
        }
    }
}
