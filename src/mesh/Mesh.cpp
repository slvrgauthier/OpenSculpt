#include "Mesh.h"

Mesh::Mesh() {  }
Mesh::~Mesh() {  }

void Mesh::clear() {  }

QString Mesh::getName() const {  }
void Mesh::setName(QString name) {  }

QVector3D Mesh::getCenter() const {  }
void Mesh::setCenter(QVector3D center) {  }

HalfEdge* Mesh::getEdge(int index) const {  }
void Mesh::setEdge(int index, HalfEdge *edge) {  }

Vertex* Mesh::getVertex(int index) const {  }
void Mesh::setVertex(int index, Vertex *vertex) {  }

Face* Mesh::getFace(int index) const {  }
void Mesh::setFace(int index, Face *face) {  }

int Mesh::getSize() const {  }

void Mesh::TEST() const {  }
