#include "MeshManager.h"

MeshManager::MeshManager() {  }
MeshManager::~MeshManager() { this->clear(); }

void MeshManager::paintGL() {
    for(int i = 0 ; i < m_renderers.size() ; ++i) {
        m_renderers[i]->paintGL();
    }
}

void MeshManager::updateMesh(int index) { m_renderers.at(index)->update(); }

void MeshManager::updateLastMesh() { if(!m_renderers.empty()) m_renderers.last()->update(); }

void MeshManager::addMesh(Mesh *mesh) {
    m_renderers.push_back(new MeshRenderer(mesh));
}

void MeshManager::removeMesh(Mesh *mesh) {
    for(int i = 0 ; i < m_renderers.size() ; ++i) {
        if(m_renderers[i]->getMesh() == mesh) {
            delete m_renderers[i];
            m_renderers.remove(i);
        }
    }
}

void MeshManager::clear() {
    for(int i = 0 ; i < m_renderers.size() ; ++i) {
        delete m_renderers[i];
    }
    m_renderers.clear();
}

Mesh* MeshManager::getMesh(int index) const { return (index >= 0 && index < m_renderers.size())? m_renderers.at(index)->getMesh() : NULL; }
int MeshManager::getSize() const { return m_renderers.size(); }
