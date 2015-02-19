#include "Mesh.h"

void Mesh::makeCone(float height, float radiusUp, float radiusDown, int discretization) {
    this->clear();

    if(radiusUp > 0 || radiusDown > 0) {
        QVector<QVector3D> face;
        float h = height/2.;
        float sizeY;

        sizeY = height /(float) discretization;

        float angle=360/(float)(8.*discretization);

        //FACE COTE
        float y = 0;
        float radiusDown_tmp,radiusUp_tmp;
        for(int i=0;i<discretization;i++){
            // gere les rayons  application du theoreme de thales
            if( i==0){
                radiusDown_tmp= radiusDown;
                radiusUp_tmp=radiusDown * (height-sizeY)  / height;
            }
            else{

                radiusDown_tmp=radiusUp_tmp;
                radiusUp_tmp=radiusDown * (height-(i+1)*sizeY)  / (height);
            }

            for(int k =0;k<8*discretization;k++){
                float resultCos= cosd(angle*k);
                float resultSin= sind(angle*k);
                float resultCos_1= cosd(angle*((k-1)%(8*discretization)));
                float resultSin_1= sind(angle*((k-1)%(8*discretization)));
                y = -h + i* sizeY;

                face.clear();
                face.push_back(QVector3D(resultCos*radiusDown_tmp, (float)y, resultSin*radiusDown_tmp));
                face.push_back(QVector3D(resultCos_1*radiusDown_tmp,(float)y, resultSin_1*radiusDown_tmp));
                face.push_back(QVector3D(resultCos_1*radiusUp_tmp,(float) y+sizeY , resultSin_1*radiusUp_tmp));
                if(radiusUp_tmp!=0)
                    face.push_back(QVector3D(resultCos*radiusUp_tmp,(float) y+sizeY, resultSin*radiusUp_tmp));

                this->addFace(face);
            }
        }


        //FACE BAS
        for(int k =0;k<8*discretization;k++){
            float resultCos= radiusDown*cosd(angle*k);
            float resultSin= radiusDown*sind(angle*k);
            float resultCos_1= radiusDown*cosd(angle*((k+1)%(8*discretization)));
            float resultSin_1= radiusDown*sind(angle*((k+1)%(8*discretization)));
            face.clear();
            face.push_back(QVector3D(0, -h, 0));
            face.push_back(QVector3D(resultCos, -h, resultSin));
            face.push_back(QVector3D(resultCos_1, -h, resultSin_1));
            this->addFace(face);

        }


        //FACE HAUT  // sens inversé par rapport au bas
        if( radiusUp !=0){
            for(int k =0;k<8*discretization;k++){
                float resultCos= radiusUp*cosd(angle*k);
                float resultSin= radiusUp*sind(angle*k);
                float resultCos_1= radiusUp*cosd(angle*((k+1)%(8*discretization)));
                float resultSin_1= radiusUp*sind(angle*((k+1)%(8*discretization)));
                face.clear();
                face.push_front(QVector3D(0, h, 0));
                face.push_front(QVector3D(resultCos, h, resultSin));
                face.push_front(QVector3D(resultCos_1, h, resultSin_1));
                this->addFace(face);

            }
        }
    }

    //this->TEST();
}
