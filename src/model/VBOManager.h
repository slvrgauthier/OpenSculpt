/*
 * VBOManager.h
 * @author : GAUTHIER Silvère
 *
 * VBOid is a structure storing informations about a buffer.
 * VBOManager controls a list of QOpenGLBuffers and gives member functions for rendering.
 *
 * A VBOManager must be given to a ModelManager to render models.
 *
 */

#ifndef VBOMANAGER_H
#define VBOMANAGER_H

#include <QOpenGLBuffer>
#include <string>
#include <vector>

using namespace std;

typedef struct VBOid {
    string name;
    int size;
} VBOid;

class VBOManager {
private :
    vector<VBOid> m_ids;
    vector<QOpenGLBuffer> m_vbos;

public:
    VBOManager();
    ~VBOManager();

    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type);
    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type, string name, int size);
    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type, string name, int size, const void* data);

    QOpenGLBuffer* getVBO(string name);
    QOpenGLBuffer* getVBO(unsigned int index);
};

#endif // VBOMANAGER_H
