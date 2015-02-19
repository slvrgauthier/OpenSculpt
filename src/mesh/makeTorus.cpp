#include "Mesh.h"

void Mesh::makeTorus(float radiusH, float radiusV, int discretization) {
    this->clear();
  int size = 8*discretization;
  QVector<QVector3D> face;
  float x=0,y=0,z=0;

  float angle = 360/(8*discretization);
  QVector<QVector3D> vertices;

  //construit les vertices
  for(int i=0;i<8.*discretization;i++){//meridien  8 meridien
    for(int k =0;k<8*discretization;k++){//parallele  9 vertices sur chaque paralleleen plus des sommets
        x=(radiusH + radiusV*cosd(angle*k))*cosd(angle*i);
        y=(radiusH + radiusV*cosd(angle*k))*sind(angle*i);
        z=radiusV*sind(angle*k);

        vertices.push_back(QVector3D(x,y,z));
      }
    }


  //Construction des faces

  for(int i=0;i<size;i++){//tore
    for(int k=0;k<size;k++){//disque
        face.clear();
        face.push_back(vertices.at(((i+1)%(size))*(size)+k));
        face.push_back(vertices.at(((i+1)%(size))*(size)+(k+1)%size));
        face.push_back(vertices.at(i*(size)+(k+1)% size));
        face.push_back(vertices.at(i*(size)+k));

        this->addFace(face);
    }
  }

    this->TEST();
}
