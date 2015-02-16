#include "Mesh.h"


void Mesh::makeSphere(float radius, int discretization) {
  this->clear();
  QVector<QVector3D> face;

  float teta=2*M_PI/(float)(8.*discretization);//meridien
  float Phi=M_PI/(float)(8.*discretization); // parrallele

 // Stocker tous les vertices.
  /*QVector3D vertices[(8*discretization)][(8*discretization)-1];
  QVector3D verticesUp,verticesDown;
  for(int i=0;i<8.*discretization;i++){//meridien
    for(int k =0;k<=8*discretization;k++){//parallele
        if(k==0)
          verticesUp=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
       else if(k==8*discretization)
          verticesDown=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
         else{
        vertices[i][k-1].setX(radius*(sinf(Phi*k)*cosf(teta*i)));
        vertices[i][k-1].setY(radius*(sinf(Phi*k)*sinf(teta*i)));
        vertices[i][k-1].setZ(radius*cosf(Phi*k));

        }

      }
    }


  //Construction des faces

  for(int i=0;i<8.*discretization;i++){//meridien
    for(int k=0;k<8*discretization-1;k++){//parallele
        if(k==0){ // face haut et premier ruban
            face.clear();
            face.push_back(verticesUp);
            face.push_back(vertices[i][k]);
            face.push_back(vertices[(i+1)%(8*discretization)][k]);
            this->addFace(face);
            face.clear();
            face.push_back(vertices[i][k]);
            face.push_back(vertices[i][k+1]);
            face.push_back(vertices[(i+1)%(8*discretization)][k+1]);
            face.push_back(vertices[(i+1)%(8*discretization)][k]);
            this->addFace(face);

          }
        else if(k==(8*discretization)-2)//face bas
          {
            face.clear();
            face.push_back(vertices[i][k]);
            face.push_back(verticesDown);
            face.push_back(vertices[(i+1)%(8*discretization)][k]);
            this->addFace(face);
          }
        else{
            face.clear();
            face.push_back(vertices[i][k]);
            face.push_back(vertices[i][k+1]);
            face.push_back(vertices[(i+1)%(8*discretization)][k+1]);
            face.push_back(vertices[(i+1)%(8*discretization)][k]);
            this->addFace(face);
        }

    }
  }
  this->TEST();
*/

}
