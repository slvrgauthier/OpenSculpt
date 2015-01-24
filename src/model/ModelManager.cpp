/*
 * ModelManager.cpp
 * @author : GAUTHIER Silvère
 *
 * Definition file of ModelManager.h.
 *
 */

#include "ModelManager.h"
#include <iostream>

using namespace std;

ModelManager::ModelManager(VBOManager *vboManager){
    m_vboManager = vboManager;
}
ModelManager::~ModelManager(){}

void ModelManager::addModel(Model *model){

    m_models.push_back(model);
/*
    ModelType type = model->getType();
    int size = model->getSize();

    float *vertices = new float[3 * size];

    for(int i = 0 ; i < 3 * size ; ++i) {
        vertices[i] = model->getNode(i)->position[i % 3];
    }

    float *indices = new float[size];

    switch(type) {
    case CUBE :
        // TODO : construct indices
        break;
    case SPHERE :
        // TODO : construct indices
        break;
    case CYLINDER :
        // TODO : construct indices
        break;
    case TORUS :
        // TODO : construct indices
        break;
    default :
        cout << "Erreur : Model added to ModelManager have a wrong type" << endl;
    }

    size *= sizeof(float);
    m_vboManager->newVBO(QOpenGLBuffer::VertexBuffer, model->getName()+"Vertex", size, vertices);
    m_vboManager->newVBO(QOpenGLBuffer::IndexBuffer, model->getName()+"Index", size, indices);

    delete[] vertices;
    delete[] indices;
*/
}
