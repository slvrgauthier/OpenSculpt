/*
 * ModelManager.h
 * @author : Team OpenSculpt
 *
 * ModelManager controls a list of Models and links these with a VBOManager for rendering.
 * Its the class used by the sculpting tools.
 *
 * Models must be added to a ModelManager to be rendered.
 *
 */

#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QVector>
#include "model/VBOManager.h"
#include "model/Model.h"

using namespace std;

class ModelManager {
private:
    VBOManager *m_vboManager;
    QVector<Model*> m_models;

public:
    ModelManager(VBOManager *vboManager);
    ~ModelManager();

    void addModel(Model *model);
    void removeModel(Model *model);

//private:

};

#endif // MODELMANAGER_H
