#include "Mesh.h"


void Mesh::makeSphere(float radius, int discretization) {
    this->clear();

    if(radius > 0) {
        QVector<QVector3D> face;
        int size = 8*discretization;
        float teta=2*M_PI/(float)(size);//meridien
        float Phi=M_PI/(float)(size); // parrallele
        float x=0,y=0,z=0;

        // Stocker tous les vertices.
        QVector<QVector3D> vertices;
        QVector3D verticesUp,verticesDown;
        for(int i=0;i<size;i++){//meridien
            for(int k =0;k<=size;k++){//parallele
                if(k==0)
                    verticesUp=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
                else if(k==size)
                    verticesDown=QVector3D(radius*(sinf(Phi*k)*cosf(teta*i)),radius*(sinf(Phi*k)*sinf(teta*i)),radius*cosf(Phi*k));
                else{
                    x=radius*(sinf(Phi*k)*cosf(teta*i));
                    y=radius*(sinf(Phi*k)*sinf(teta*i));
                    z=radius*cosf(Phi*k);

                    vertices.push_back(QVector3D(x,y,z));
                }

            }
        }


        //Construction des faces

        for(int i=0;i<size;i++){//meridien
            for(int k=0;k<size-1;k++){//parallele
                if(k==0){ // face haut et premier ruban
                    face.clear();
                    face.push_back(verticesUp);
                    face.push_back(vertices.at(i*(size-1)+k));
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k));
                    this->addFace(face);
                    face.clear();
                    face.push_back(vertices.at(i*(size-1)+k));
                    face.push_back(vertices.at(i*(size-1)+k+1));
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k+1));
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k));
                    this->addFace(face);

                }
                else if(k==(size)-2)//face bas
                {
                    face.clear();
                    face.push_back(vertices.at(i*(size-1)+k));
                    face.push_back(verticesDown);
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k));
                    this->addFace(face);
                }
                else{
                    face.clear();
                    face.push_back(vertices.at(i*(size-1)+k));
                    face.push_back(vertices.at(i*(size-1)+k+1));
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k+1));
                    face.push_back(vertices.at(((i+1)%(size))*(size-1)+k));
                    this->addFace(face);
                }

            }
        }
    }
    //this->TEST();
}
