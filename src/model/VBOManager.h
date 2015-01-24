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
#include <QString>
#include <QVector>

using namespace std;

typedef struct VBOid {
    QString name;
    int size;
} VBOid;

class VBOManager {
private :
    QVector<VBOid> m_ids;
    QVector<QOpenGLBuffer> m_vbos;

public:
    VBOManager();
    ~VBOManager();

    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type);
    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type, QString name, int size);
    QOpenGLBuffer* newVBO(QOpenGLBuffer::Type type, QString name, int size, const void* data);

    QOpenGLBuffer* getVBO(QString name);
    QOpenGLBuffer* getVBO(int index);
};

#endif // VBOMANAGER_H
