/*
 * ModelManager.cpp
 * @author : Team OpenSculpt
 *
 * Definition file of ModelManager.h.
 *
 */

#include "ModelManager.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
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

void ModelManager::removeModel()
{
    m_models.removeLast();
}

QVector3D ModelManager::getGLpos(QPoint mouse)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    float x = mouse.x(), y = mouse.y();
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;

    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    if(winZ == 1 || winZ == 0) {
        return QVector3D();
    }
    else {
        gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
        return QVector3D(posX, posY, posZ); // position 3D du pixel touché
    }
}

Model* ModelManager::pickModel(QVector3D position)
{

}
