#include "model/MCube.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#endif

MCube::MCube() : m_width(5.0), m_height(5.0), m_depth(5.0)
{
    // Load model : RECODE to merge multiple points
    vertices_by_x = 10;
    vertices_by_y = 10;
    vertices_by_z = 10;
    quads_by_x = vertices_by_x - 1;
    quads_by_y = vertices_by_y - 1;
    quads_by_z = vertices_by_z - 1;

    // Vertices
    QVector3D vertice;
    m_vertices.reserve(vertices_by_x * vertices_by_y * vertices_by_z);
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int y = 0; y < vertices_by_y; ++y)
        {
            for(int x = 0; x < vertices_by_x; ++x)
            {
                vertice.setX((m_width * x / quads_by_x) - m_width / 2);
                vertice.setY((m_height * y / quads_by_y) - m_height / 2);
                vertice.setZ((m_depth * z / quads_by_z) - m_depth / 2);
                m_vertices.push_back(vertice);
            }
        }
    }

    // Indices
    m_indices.reserve(quads_by_x * quads_by_y * quads_by_z * 6);
    for (int z = 0; z <= quads_by_z; z+=quads_by_z) // Front and Back
    {
        for (int y = 0; y < quads_by_y; ++y)
        {
            for (int x = 0; x < quads_by_x; ++x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                m_indices.push_back(i);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + 1);

                m_indices.push_back(i + 1);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + 1 + vertices_by_x);
            }
        }
    }
    for (int z = 0; z < quads_by_z; ++z) // Up and Down
    {
        for (int y = 0; y <= quads_by_y; y+=quads_by_y)
        {
            for (int x = 0; x < quads_by_x; ++x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                m_indices.push_back(i);
                m_indices.push_back(i + vertices_by_y * vertices_by_x);
                m_indices.push_back(i + 1);

                m_indices.push_back(i + 1);
                m_indices.push_back(i + vertices_by_y * vertices_by_x);
                m_indices.push_back(i + 1 + vertices_by_y * vertices_by_x);
            }
        }
    }
    for (int z = 0; z < quads_by_z; ++z) // Left and Right
    {
        for (int y = 0; y < quads_by_y; ++y)
        {
            for (int x = 0; x <= quads_by_x; x+=quads_by_x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                m_indices.push_back(i);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + vertices_by_y * vertices_by_x);

                m_indices.push_back(i + vertices_by_y * vertices_by_x);
                m_indices.push_back(i + vertices_by_x);
                m_indices.push_back(i + vertices_by_y * vertices_by_x + vertices_by_x);
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
}

void MCube::initializeGL()
{

}

void MCube::paintGL()
{
    glEnableClientState(GL_VERTEX_ARRAY);

    m_vertexbuffer.bind();
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    m_vertexbuffer.release();

    m_indicebuffer.bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    m_indicebuffer.release();

    glDisableClientState(GL_VERTEX_ARRAY);
}
#include <QDebug>
void MCube::setWidth(float width)
{
    qDebug()<<"hey !";
    int i;
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int y = 0; y < vertices_by_y; ++y)
        {
            for(int x = 0; x < vertices_by_x; ++x)
            {
                i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;
                m_vertices[i].setX((width * x / quads_by_x) - width / 2);
            }
        }
    }
    m_width = width;

    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();
}

void MCube::setHeight(float height)
{
    int i;
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int y = 0; y < vertices_by_y; ++y)
        {
            for(int x = 0; x < vertices_by_x; ++x)
            {
                i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;
                m_vertices[i].setY((height * y / quads_by_y) - height / 2);
            }
        }
    }
    m_height = height;

    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();
}

void MCube::setDepth(float depth)
{
    int i;
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int y = 0; y < vertices_by_y; ++y)
        {
            for(int x = 0; x < vertices_by_x; ++x)
            {
                i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;
                m_vertices[i].setZ((depth * z / quads_by_z) - depth / 2);
            }
        }
    }
    m_depth = depth;

    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();
}

