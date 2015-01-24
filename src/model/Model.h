/*
 * Model.h
 * @author : GAUTHIER Silvère
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
    float position[3];
    QVector<Node*> neighbours;
} Node;*/

class Model : public QGLWidget
{
    Q_OBJECT
public:
    explicit Model(QWidget *parent = 0);
    ~Model();

public:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void rotateBy(int x, int y, int z);


public:
    QString getName() const;
    void setName(QString name);
    /*
    ModelType getType() const;
    unsigned int getSize() const;
    Node* getNode(unsigned int index);

    // The four functions below erase the previous data.
    void makeCube(float width, float height, float depth, unsigned int resolution);
    void makeSphere(float radius, unsigned int resolution);
    void makeCylinder(float radius1, float radius2, float height, unsigned int resolution);
    void makeTorus(float radius1, float radius2, unsigned int resolution);
    */
private:
    // Model infos
    int vertices_by_x;
    int vertices_by_y;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_y;
    int quads_by_z;
    QString m_name;
    //QVector<Node> m_data;

    // 3D / 2D coords
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_vertexarray;
    QVector<GLuint>    m_indices;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;
    QGLBuffer m_indicebuffer;

    // View & rotation settings
    QPoint last_pos;
    float  distance;
    qreal  x_rot;
    qreal  y_rot;
    qreal  z_rot;

    // Render settings
    bool mode_fill;
};

#endif // MODEL_H
