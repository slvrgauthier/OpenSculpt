/*
 * ModelManager.cpp
 * @author : Team OpenSculpt
 *
 * Definition file of ModelManager.h.
 *
 */

#include "ModelManager.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>*/
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

using namespace std;

ModelManager::ModelManager(){}
ModelManager::~ModelManager(){}

void ModelManager::initializeGL()
{
    for(int i = 0 ; i < m_models.size() ; ++i) {
        m_models[i]->initializeGL();
    }
}

void ModelManager::paintGL()
{
    for(int i = 0 ; i < m_models.size() ; ++i) {
        m_models[i]->paintGL();
    }
}

void ModelManager::addModel(Model *model) { m_models.push_back(model); }

void ModelManager::removeModel() { m_models.removeLast(); }

void ModelManager::clear() { m_models.clear(); }

Model* ModelManager::getModel(int index) {
    if(m_models.size() > index && index >= 0) {
        return m_models.at(index);
    }
    return NULL;
}
