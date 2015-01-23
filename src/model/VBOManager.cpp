#include <iostream>
#include "VBOManager.h"

using namespace std;

VBOManager::VBOManager(){
    m_ids = vector<VBOid>();
    m_vbos = vector<QOpenGLBuffer>();
}

VBOManager::~VBOManager(){
    // TODO
}


QOpenGLBuffer* VBOManager::newVBO(){
    return this->newVBO(0, GL_FLOAT, NULL, NULL);
}

QOpenGLBuffer* VBOManager::newVBO(string name){
    return this->newVBO(0, GL_FLOAT, NULL, name);
}

QOpenGLBuffer* VBOManager::newVBO(unsigned int size, GLenum type){
    return this->newVBO(size, type, NULL, NULL);
}

QOpenGLBuffer* VBOManager::newVBO(unsigned int size, GLenum type, string name){
    return this->newVBO(size, type, NULL, name);
}

QOpenGLBuffer* VBOManager::newVBO(unsigned int size, GLenum type, const void *data){
    return this->newVBO(size, type, data, NULL);
}

QOpenGLBuffer* VBOManager::newVBO(unsigned int size, GLenum type, const void *data, string name){

    QOpenGLBuffer vbo(QOpenGLBuffer::VertexBuffer);
    vbo.setUsagePattern(QOpenGLBuffer::StreamDraw);

    if(!vbo.bind()){
        cout << "Error : Unable to bind the buffer to the current QOpenGLContext" << endl;
        exit(1);
    }
    if(!vbo.create()){
        cout << "Error : Unable to create the buffer" << endl;
        exit(1);
    }

    VBOid id;
    id.name = name;
    id.size = size * sizeof(type);

    m_ids.push_back(id);
    m_vbos.push_back(vbo);

    if(size > 0) {
        if(data != NULL) {
            vbo.allocate(data, id.size);
        }
        else {
            vbo.allocate(id.size);
        }
    }

    vbo.release();

    return &m_vbos.back();
}


QOpenGLBuffer* VBOManager::getVBO(string name) {
    for(unsigned int i=0 ; i < m_vbos.size() ; ++i) {
        if(name == m_ids[i].name) {
            return &m_vbos[i];
        }
    }
    return 0;
}

QOpenGLBuffer* VBOManager::getVBO(unsigned int index) {
    if(index < m_vbos.size()) {
        return &m_vbos[index];
    }
    else {
        return NULL;
    }
}
