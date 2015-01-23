#include <iostream>
#include "model/VBOManager.h"

using namespace std;

VBOManager::VBOManager(){
    m_ids = vector<VBOid>();
    m_vbos = vector<QOpenGLBuffer>();
}

VBOManager::~VBOManager(){
    // TODO
}


QOpenGLBuffer* VBOManager::newVBO(QOpenGLBuffer::Type type){
    return this->newVBO(type, string(), 0, NULL);
}

QOpenGLBuffer* VBOManager::newVBO(QOpenGLBuffer::Type type, string name, int size){
    return this->newVBO(type, name, size, NULL);
}

QOpenGLBuffer* VBOManager::newVBO(QOpenGLBuffer::Type type, string name, int size, const void *data){

    QOpenGLBuffer vbo(type);
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
    id.size = size;

    m_ids.push_back(id);
    m_vbos.push_back(vbo);

    if(size > 0) {
        if(data != NULL) {
            vbo.allocate(data, size);
        }
        else {
            vbo.allocate(size);
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
