#include "model/MCube.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

const float MAP_SIZE = 5.0;

void MCube::initializeGL()
{
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
    for (int z = 0; z <= quads_by_z; z+=quads_by_z)
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
    for (int z = 0; z < quads_by_z; ++z)
    {
        for (int y = 0; y <= quads_by_y; y+=quads_by_y)
        {
            for (int x = 0; x < quads_by_x; ++x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                // VertexArray
                m_vertexarray.push_back(m_vertices[i]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_y * vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+1]);

                m_vertexarray.push_back(m_vertices[i+1]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_y * vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+1+vertices_by_y * vertices_by_x]);

                // Indices
                m_indices.push_back(i);
                m_indices.push_back(i + vertices_by_y * vertices_by_x);
                m_indices.push_back(i + 1);

                m_indices.push_back(i + 1);
                m_indices.push_back(i + vertices_by_y * vertices_by_x);
                m_indices.push_back(i + 1 + vertices_by_y * vertices_by_x);
            }
        }
    }
    for (int z = 0; z < quads_by_z; ++z)
    {
        for (int y = 0; y < quads_by_y; ++y)
        {
            for (int x = 0; x <= quads_by_x; x+=quads_by_x)
            {
                int i = z * vertices_by_y * vertices_by_x + y * vertices_by_x + x;

                // VertexArray
                m_vertexarray.push_back(m_vertices[i]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_y * vertices_by_x]);

                m_vertexarray.push_back(m_vertices[i+vertices_by_y * vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
                m_vertexarray.push_back(m_vertices[i+vertices_by_y * vertices_by_x+vertices_by_x]);

                // Indices
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
