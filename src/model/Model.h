/*
 * Model.h
 * @author : Team OpenSculpt
 *
 * Node represent a node of our internal mesh, with 3D position and neighbourhood.
 * Model is a mesh defined by a list of Nodes and let the user create base meshes.
 *
 * Models must be added to a ModelManager to be rendered.
 *
 */

#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QVector>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>
#include <QString>

using namespace std;
/*
typedef struct Node {
    QVector<Node*> neighbours;
} Node;*/

class Model : public QGLWidget
{
    Q_OBJECT
public:
    explicit Model(QWidget *parent = 0);

public:
    virtual void initializeGL();
    virtual void paintGL();

    QString getName() const;
    void setName(QString name);

protected:
    // Model infos
    QString m_name;
    //QVector<Node> m_data;

    // 3D / 2D coords
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_vertexarray;
    QVector<GLuint>    m_indices;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;
    QGLBuffer m_indicebuffer;
};

#endif // MODEL_H
