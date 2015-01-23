#include "ModelManager.h"
#include <iostream>

using namespace std;

ModelManager::ModelManager(VBOManager *vboManager){
    m_vboManager = vboManager;
}
ModelManager::~ModelManager(){}

void ModelManager::addModel(Model *model){

    m_models.push_back(model);

    //créer VBO avec tableau indice selon le type
    ModelType type = model->getType();

    switch(type) {
    case CUBE :
        break;
    case SPHERE :
        break;
    case CYLINDER :
        break;
    case TORUS :
        break;
    default :
        cout << "Erreur : Model added to ModelManager have a wrong type" << endl;
    }
}
