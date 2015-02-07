#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(Mesh *mesh) {
    m_vertexbuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    m_indicebuffer = new QGLBuffer(QGLBuffer::IndexBuffer);
    m_mesh = mesh;
}

MeshRenderer::~MeshRenderer() {
    delete m_mesh;
    m_vertexbuffer->destroy();
    m_indicebuffer->destroy();
}

void MeshRenderer::paintGL() {
    glEnableClientState(GL_VERTEX_ARRAY);

    m_vertexbuffer->bind();
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    m_vertexbuffer->release();

    m_indicebuffer->bind();
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    m_indicebuffer->release();

    glDisableClientState(GL_VERTEX_ARRAY);
}

void MeshRenderer::update() {

    // Convertir le maillage interne pour le rendu
    m_coords.clear();
    m_coords.reserve(m_mesh->getVertexCount());
    for(int i=0 ; i < m_mesh->getVertexCount() ; ++i) {
        m_coords.push_back(m_mesh->getVertex(i)->coords);
    }

    m_indices.clear();
    m_indices.reserve(m_mesh->getFaceCount() * 3);
    for(int i=0 ; i < m_mesh->getFaceCount() ; ++i) {
        m_indices.push_back(m_mesh->getFace(i)->edge->vertex->index);
        m_indices.push_back(m_mesh->getFace(i)->edge->next->vertex->index);
        m_indices.push_back(m_mesh->getFace(i)->edge->previous->vertex->index);
    }

    // Vertex buffer init
    if(m_vertexbuffer->isCreated() && m_vertexbuffer->size() >= m_coords.size()) {
        m_vertexbuffer->bind();
        m_vertexbuffer->write(0, m_coords.constData(), m_coords.size() * sizeof(QVector3D));
        m_vertexbuffer->release();
    }
    else {
        m_vertexbuffer->destroy();
        m_vertexbuffer->create();
        m_vertexbuffer->bind();
        m_vertexbuffer->allocate(m_coords.constData(), m_coords.size() * sizeof(QVector3D));
        m_vertexbuffer->release();
    }

    // Indices buffer init
    if(m_indicebuffer->isCreated() && m_indicebuffer->size() >= m_indices.size()) {
        m_indicebuffer->bind();
        m_indicebuffer->write(0, m_indices.constData(), m_indices.size() * sizeof(GLuint));
        m_indicebuffer->release();
    }
    else {
        m_indicebuffer->destroy();
        m_indicebuffer->create();
        m_indicebuffer->bind();
        m_indicebuffer->allocate(m_indices.constData(), m_indices.size() * sizeof(GLuint));
        m_indicebuffer->release();
    }
}

Mesh* MeshRenderer::getMesh() const { return m_mesh; }
