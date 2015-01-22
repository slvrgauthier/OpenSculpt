#include "VBOManager.h"

/** PRIVATE MEMBERS **/

void VBOManager::alloc(GLuint vbo, GLsizei size){
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//void VBOManager::realloc(GLuint vbo, GLsizei size){}


/** PUBLIC MEMBERS **/

VBOManager::VBOManager(){
    m_vbos = vector<VBO>();
}

VBOManager::~VBOManager(){
    for(unsigned int i=0 ; i < m_vbos.size() ; ++i) {
        this->deleteVBO(m_vbos[0].m_id);
        m_vbos.erase(m_vbos.begin());
    }
}


GLuint VBOManager::newVBO(){
    return this->newVBO(0, GL_FLOAT, NULL);
}

GLuint VBOManager::newVBO(string name){
    return this->newVBO(0, GL_FLOAT, name);
}

GLuint VBOManager::newVBO(unsigned int size, GLenum type){
    return this->newVBO(size, type, NULL);
}

GLuint VBOManager::newVBO(unsigned int size, GLenum type, string name){
    GLuint id = 0;
    //glGenBuffers(1, &id);

    VBO vbo;
    vbo.m_id = id;
    vbo.m_name = name;
    vbo.m_size = size * sizeof(type);

    m_vbos.push_back(vbo);

    if(size > 0) {
        this->alloc(id, vbo.m_size);
    }

    return id;
}


void VBOManager::deleteVBO(GLuint &vbo){
    //glDeleteBuffers(1, vbo);
}


GLuint VBOManager::getVBO(string name) const{
    for(unsigned int i=0 ; i < m_vbos.size() ; ++i) {
        if(name == m_vbos[i].m_name) {
            return m_vbos[i].m_id;
        }
    }
    return 0;
}

GLuint VBOManager::getVBO(unsigned int index) const{
    if(index < m_vbos.size()) {
        return m_vbos[index].m_id;
    }
    else {
        return 0;
    }
}
