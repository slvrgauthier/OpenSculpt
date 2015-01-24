/*
 * Model.cpp
 * @author : GAUTHIER Silvère
 *
 * Definition file of Model.h.
 *
 */

#include "model/Model.h"
#include "func/functions.h"
#include <QtGui/QMouseEvent>
#include <GL/glut.h>

const float MAP_SIZE = 5.0;

Model::Model(QWidget *parent):
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    m_indicebuffer(QGLBuffer::IndexBuffer)
{
    // Render mode set up
    mode_fill = true;
}

Model::~Model()
{
    // TODO
}

void Model::initializeGL()
{
    // View & rotation settings
    distance = -10.0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;

    // Load model : RECODE to keep only borders
    vertices_by_x = 10;
    vertices_by_y = 10;
    vertices_by_z = 10;
    quads_by_x = vertices_by_x - 1;
    quads_by_y = vertices_by_y - 1;
    quads_by_z = vertices_by_z - 1;

    QVector3D vertice;
    m_vertices.reserve(vertices_by_x * vertices_by_y * vertices_by_z);
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int y = 0; y < vertices_by_y; ++y)
        {
            for(int x = 0; x < vertices_by_x; ++x)
            {
                vertice.setX((MAP_SIZE * x / vertices_by_x) - MAP_SIZE / 2);
                vertice.setY((MAP_SIZE * y / vertices_by_y) - MAP_SIZE / 2);
                vertice.setZ((MAP_SIZE * z / vertices_by_z) - MAP_SIZE / 2);
                m_vertices.push_back(vertice);
            }
        }
    }

    // Vertex array & indices
    m_vertexarray.reserve(quads_by_x * quads_by_y * quads_by_z * 6);
    m_indices.reserve(quads_by_x * quads_by_y * quads_by_z * 6);
    for (int z = 0; z < quads_by_z; ++z)
    {
        for (int y = 0; y < quads_by_y; ++y)
        {
            for (int x = 0; x < quads_by_x; ++x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                // VertexArray
                m_vertexarray.push_back(m_vertices[i]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+1]);

                m_vertexarray.push_back(m_vertices[i+1]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+1+vertices_by_x]);

                // Indices
                m_indices.push_back(i);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + 1);

                m_indices.push_back(i + 1);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + 1 + vertices_by_x);
            }
        }
    }

    // Vertex buffer init
    m_vertexbuffer.create();
    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();

    // Indices buffer init
    m_indicebuffer.create();
    m_indicebuffer.bind();
    m_indicebuffer.allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));
    m_indicebuffer.release();

    // GL options
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
}

void Model::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, mode_fill ? GL_FILL : GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -distance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot / 16.0f, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // Draw map
    qglColor(Qt::white);

    glEnableClientState(GL_VERTEX_ARRAY);

    m_vertexbuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    m_vertexbuffer.release();

    m_indicebuffer.bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    m_indicebuffer.release();

    glDisableClientState(GL_VERTEX_ARRAY);
}

void Model::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Model::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F)
        mode_fill = !mode_fill;
}

void Model::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void Model::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_pos.x();
    int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::RightButton)
    {
        rotateBy(dy*8, 0, 0);
        rotateBy(0, dx*8, 0);
    }
    last_pos = event->pos();
}

void Model::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 - (1.0 * event->delta() / 1200.0);
}

void Model::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}


QString Model::getName() const { return m_name; }
void Model::setName(QString name) { m_name = name; }
/*
ModelType Model::getType() const { return m_type; }
unsigned int Model::getSize() const { return m_data.size(); }
Node* Model::getNode(unsigned int index) { return &m_data[index]; }


void Model::makeCube(float width, float height, float depth, unsigned int resolution){

    m_type = CUBE;
    m_data.clear();

    Node tmpNode;

    // Left and Right sides
    for(float x = -width/2 ; x <= width/2 ; x += width) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height/resolution) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth/resolution) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    // Up and Down sides
    for(float x = -width/2 ; x <= width/2 ; x += width/resolution) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth/resolution) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    // Front and Back sides
    for(float x = -width/2 ; x <= width/2 ; x += width/resolution) {

        tmpNode.position[0] = x;

        for(float y = -height/2 ; y <= height/2 ; y += height/resolution) {

            tmpNode.position[1] = y;

            for(float z = -depth/2 ; z <= depth/2 ; z += depth) {

                tmpNode.position[2] = z;

                m_data.push_back(tmpNode);
            }
        }
    }

    for(int i = 0 ; i < m_data.size()-1 ; ++i) {
        for(int j = i+1 ; j < m_data.size() ; ++j) {
            if(i != j && !contains(m_data[i].neighbours, &m_data[j])) {
                if((unsigned)(m_data[i].position[0] - m_data[j].position[0]) == width/resolution
                        || (unsigned)(m_data[i].position[1] - m_data[j].position[1]) == height/resolution
                        || (unsigned)(m_data[i].position[2] - m_data[j].position[2]) == depth/resolution) {
                    m_data[i].neighbours.push_back(&m_data[j]);
                    m_data[j].neighbours.push_back(&m_data[i]);
                }
            }
        }
    }
}

void Model::makeSphere(float radius, unsigned int resolution){
    // TODO
}

void Model::makeCylinder(float radius1, float radius2, float height, unsigned int resolution){
    // TODO
}

void Model::makeTorus(float radius1, float radius2, unsigned int resolution){
    // TODO
}
*/
