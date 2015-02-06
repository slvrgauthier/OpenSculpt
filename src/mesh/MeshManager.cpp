#include "MeshManager.h"

MeshManager::MeshManager() {  }
MeshManager::~MeshManager() { this->clear(); }

void MeshManager::paintGL() {
    for(int i = 0 ; i < m_renderers.size() ; ++i) {
        m_renderers[i]->paintGL();
    }
}

void MeshManager::addMesh(Mesh *mesh) {
    m_renderers.push_back(new MeshRenderer(mesh));
}

void MeshManager::removeMesh() {
    delete m_renderers.last();
    m_renderers.removeLast();
}

void MeshManager::clear() {
    for(int i = 0 ; i < m_renderers.size() ; ++i) {
        delete m_renderers[i];
    }
    m_renderers.clear();
}

Mesh* MeshManager::getMesh(int index) { return m_renderers.at(index)->getMesh(); }
