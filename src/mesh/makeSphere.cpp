#include "Mesh.h"

void Mesh::makeSphere(float radius, int discretization) {

  QVector<QVector3D> face;
  //float h = height/2.;
  float sizeY;
  //sizeY = height /(float) discretization;
  float teta=360/(float)(8.*discretization);
  float Phi=M_PI/(float)(8.*discretization);//M_PI/


  //FACE COTE
  float y = 0;
  for(int i=0;i<8.*discretization;i++){//meridien
    for(int k =0;k<(8*discretization);k++){//parallele
        //reference
        float resSinCos=radius*(sinf(Phi*k)*cosd(teta*i)); //X
        float resSinSin=radius*(sinf(Phi*k)*sind(teta*i));  //Y
        float resCos=radius*cosf(Phi*k);  //Z

        float resSinCos_1=radius*(sinf(Phi*(k+1))*cosd(teta*i)); //X par+1
        float resSinSin_1=radius*(sinf(Phi*(k+1))*sind(teta*i));  //Y para+1
        float resCos_1=radius*cosf(Phi*(k+1));  //Z para+1

        float resSinCos_1_1=radius*(sinf(Phi*(k+1))*cosd(teta*((i+1)%(8*discretization)))); //X par+1 meri+1
        float resSinSin_1_1=radius*(sinf(Phi*(k+1))*sind(teta*((i+1)%(8*discretization))));  //Y para+1 merid+1

        float resSinCos_0_1=radius*(sinf(Phi*(k))*cosd(teta*((i+1)%(8*discretization)))); //X  meri+1
        float resSinSin_0_1=radius*(sinf(Phi*(k))*sind(teta*((i+1)%(8*discretization))));  //Y  merid+1

      if(k==0){
          face.clear();
          face.push_back(QVector3D(resSinCos,resSinSin,resCos ));
          face.push_back(QVector3D(resSinCos_1,resSinSin_1,resCos_1));
          face.push_back(QVector3D(resSinCos_1_1,resSinSin_1_1,resCos_1));
          this->addFace(face);
        }
      else if(k==(8*discretization)-1)
        {
          face.clear();
          face.push_back(QVector3D(resSinCos,resSinSin,resCos ));
          face.push_back(QVector3D(resSinCos_1,resSinSin_1,resCos_1));
          face.push_back(QVector3D(resSinCos_0_1,resSinSin_0_1,resCos));
          this->addFace(face);
        }
      else{
      face.clear();
      face.push_back(QVector3D(resSinCos,resSinSin,resCos ));
      face.push_back(QVector3D(resSinCos_1,resSinSin_1,resCos_1));
      face.push_back(QVector3D(resSinCos_1_1,resSinSin_1_1,resCos_1));
      face.push_back(QVector3D(resSinCos_0_1,resSinSin_0_1,resCos));
      this->addFace(face);
        }
    }
  }

//this->TEST();


}
