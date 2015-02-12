#include "Mesh.h"

void Mesh::makeCylinder(float height, float radius, int discretization) {
    this->clear();

  QVector<QVector3D> face;
  float h = height/2.;
  float sizeY;

  sizeY = height /(float) discretization;

  float angle=360/(float)(8.*discretization);

  //FACE COTE
  float y = 0;
  for(int i=0;i<discretization;i++){
    for(int k =0;k<8*discretization;k++){
      float resultCos= radius*cosd(angle*k);
      float resultSin= radius*sind(angle*k);
      float resultCos_1= radius*cosd(angle*((k-1)%(8*discretization)));
      float resultSin_1= radius*sind(angle*((k-1)%(8*discretization)));
      y = -h + i* sizeY;
      face.clear();
      face.push_back(QVector3D(resultCos, (float)y, resultSin));
      face.push_back(QVector3D(resultCos_1,(float)y, resultSin_1));
      face.push_back(QVector3D(resultCos_1,(float) y + sizeY , resultSin_1));
      face.push_back(QVector3D(resultCos,(float) y + sizeY, resultSin));
      this->addFace(face);

    }
  }


  //FACE BAS
  for(int k =0;k<8*discretization;k++){
      float resultCos= radius*cosd(angle*k);
      float resultSin= radius*sind(angle*k);
      float resultCos_1= radius*cosd(angle*((k+1)%(8*discretization)));
      float resultSin_1= radius*sind(angle*((k+1)%(8*discretization)));
      face.clear();
      face.push_back(QVector3D(0, -h, 0));
      face.push_back(QVector3D(resultCos, -h, resultSin));
      face.push_back(QVector3D(resultCos_1, -h, resultSin_1));
      this->addFace(face);

    }


  //FACE HAUT  // sens inversé par rapport au bas
  for(int k =0;k<8*discretization;k++){
      float resultCos= radius*cosd(angle*k);
      float resultSin= radius*sind(angle*k);
      float resultCos_1= radius*cosd(angle*((k+1)%(8*discretization)));
      float resultSin_1= radius*sind(angle*((k+1)%(8*discretization)));
      face.clear();
      face.push_front(QVector3D(0, h, 0));
      face.push_front(QVector3D(resultCos, h, resultSin));
      face.push_front(QVector3D(resultCos_1, h, resultSin_1));
      this->addFace(face);

    }
//this->TEST();


}
