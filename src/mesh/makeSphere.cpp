#include "Mesh.h"

void Mesh::makeSphere(float radius, int discretization) {

  QVector<QVector3D> face;

  float teta=2*M_PI/(float)(8.*discretization);
  float Phi=M_PI/(float)(8.*discretization);


/*
  //FACE COTE
  //float y = 0;
  QVector3D points[(8*discretization)][(8*discretization)-1];
  QVector3D pointhaut,pointBas;
  for(int i=0;i<8.*discretization;i++){//meridien  8 meridien
    for(int k =0;k<=8*discretization;k++){//parallele  9 points sur chaque paralleleen plus des sommets

        // Stocker tous les points.
        if(k==0)
          pointhaut=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
       else if(k==8*discretization)
          pointBas=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
         else{
        points[i][k].setX(radius*(sinf(Phi*k)*cosf(teta*i)));
        points[i][k].setY(radius*(sinf(Phi*k)*sinf(teta*i)));
        points[i][k].setZ(radius*cosf(Phi*k));

        }

      }
    }

  //Construction des faces

  for(int i=0;i<8.*discretization;i++){//meridien
    for(int k=0;k<8*discretization;k++){//parallele
        if(k==0){
            face.clear();
            face.push_back(pointhaut);
            face.push_back(points[i][k]);
            face.push_back(points[(i+1)%(8*discretization)][k]);
            this->addFace(face);
          }
        else if(k==(8*discretization)-1)
          {
            face.clear();
            face.push_back(points[i][k]);
            face.push_back(pointBas);
            face.push_back(points[(i+1)%(8*discretization)][k]);
            this->addFace(face);
          }
        else{
            face.clear();
            face.push_back(points[i][k]);
            face.push_back(points[i][k+1]);
            face.push_back(points[(i+1)%(8*discretization)][k+1]);
            face.push_back(points[(i+1)%(8*discretization)][k]);
            this->addFace(face);
        }


    }
  }
  this->TEST();
*/

}
