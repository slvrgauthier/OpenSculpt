#include "Mesh.h"

void Mesh::makeTorus(float radiusH, float radiusV, int discretization) {
    this->clear();

  QVector<QVector3D> face;

  float angle = 360/(8*discretization);
  QVector3D vertices[(8*discretization)][(8*discretization)];

  //construit les vertices
  for(int i=0;i<8.*discretization;i++){//meridien  8 meridien
    for(int k =0;k<8*discretization;k++){//parallele  9 vertices sur chaque paralleleen plus des sommets
        vertices[i][k].setX((radiusH + radiusV*cosd(angle*k))*cosd(angle*i));
        vertices[i][k].setY((radiusH + radiusV*cosd(angle*k))*sind(angle*i));
        vertices[i][k].setZ(radiusV*sind(angle*k));
      }
    }


  //Construction des faces

  for(int i=0;i<8.*discretization;i++){//tore
    for(int k=0;k<8*discretization;k++){//disque
        face.clear();
        face.push_front(vertices[i][k]);
        face.push_front(vertices[i][(k+1)%(8*discretization)]);
        face.push_front(vertices[(i+1)%(8*discretization)][(k+1)%(8*discretization)]);
        face.push_front(vertices[(i+1)%(8*discretization)][k]);
        this->addFace(face);
    }
  }

    this->TEST();
}
