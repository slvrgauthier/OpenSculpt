#ifndef VBOMANAGER_H
#define VBOMANAGER_H

#include <GL/glew.h>
#include <QOpenGLBuffer>
#include <string>
#include <vector>

using namespace std;

typedef struct VBOid {
    string name;
    unsigned int size;
} VBOid;

class VBOManager {
private :
    vector<VBOid> m_ids;
    vector<QOpenGLBuffer> m_vbos;

public:
    VBOManager();
    ~VBOManager();

    QOpenGLBuffer* newVBO();
    QOpenGLBuffer* newVBO(string name);
    QOpenGLBuffer* newVBO(unsigned int size, GLenum type);
    QOpenGLBuffer* newVBO(unsigned int size, GLenum type, string name);
    QOpenGLBuffer* newVBO(unsigned int size, GLenum type, const void *data);
    QOpenGLBuffer* newVBO(unsigned int size, GLenum type, const void* data, string name);

    QOpenGLBuffer* getVBO(string name);
    QOpenGLBuffer* getVBO(unsigned int index);

//public slots:


//signals:

};

#endif // VBOMANAGER_H
