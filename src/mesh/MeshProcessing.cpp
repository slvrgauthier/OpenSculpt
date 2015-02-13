#include "MeshProcessing.h"

MeshProcessing::MeshProcessing() {  }
MeshProcessing::~MeshProcessing() {  }

void MeshProcessing::subdivide(Mesh *mesh) {

    int size = mesh->getFaceCount();

    for(int i=0 ; i < size ; ++i) {

        Vertex *v1, *v2, *v3;

        for(int j=0 ; j < 3 ; ++j) { mesh->addFace(new Face); }
        for(int j=0 ; j < 9 ; ++j) { mesh->addEdge(new HalfEdge); }

        // Milieux des trois demi-arêtes de la face i
        if(mesh->getFace(i)->edge == mesh->getFace(i)->edge->opposite->previous->opposite->previous->opposite->previous->opposite) {
            // Le milieu existe déjà
            v1 = mesh->getFace(i)->edge->opposite->previous->vertex;
        }
        else {
            // Le milieu n'existe pas
            mesh->addVertex(new Vertex);
            v1 = mesh->getVertex(mesh->getVertexCount()-1);
            v1->index = mesh->getVertexCount()-1;
            v1->outgoing = mesh->getEdge(mesh->getEdgeCount()-7);
            v1->coords = (mesh->getFace(i)->edge->vertex->coords + mesh->getFace(i)->edge->previous->vertex->coords) / 2;
        }
        if(mesh->getFace(i)->edge->next == mesh->getFace(i)->edge->next->opposite->previous->opposite->previous->opposite->previous->opposite) {
            // Le milieu existe déjà
            v2 = mesh->getFace(i)->edge->next->opposite->previous->vertex;
        }
        else {
            // Le milieu n'existe pas
            mesh->addVertex(new Vertex);
            v2 = mesh->getVertex(mesh->getVertexCount()-1);
            v2->index = mesh->getVertexCount()-1;
            v2->outgoing = mesh->getEdge(mesh->getEdgeCount()-8);
            v2->coords = (mesh->getFace(i)->edge->vertex->coords + mesh->getFace(i)->edge->next->vertex->coords) / 2;
        }
        if(mesh->getFace(i)->edge->previous == mesh->getFace(i)->edge->previous->opposite->previous->opposite->previous->opposite->previous->opposite) {
            // Le milieu existe déjà
            v3 = mesh->getFace(i)->edge->previous->opposite->previous->vertex;
        }
        else {
            // Le milieu n'existe pas
            mesh->addVertex(new Vertex);
            v3 = mesh->getVertex(mesh->getVertexCount()-1);
            v3->index = mesh->getVertexCount()-1;
            v3->outgoing = mesh->getEdge(mesh->getEdgeCount()-9);
            v3->coords = (mesh->getFace(i)->edge->next->vertex->coords + mesh->getFace(i)->edge->previous->vertex->coords) / 2;
        }

        // Trois nouvelles faces créées
        mesh->getFace(mesh->getFaceCount()-1)->edge = mesh->getFace(i)->edge;
        mesh->getFace(mesh->getFaceCount()-2)->edge = mesh->getFace(i)->edge->next;
        mesh->getFace(mesh->getFaceCount()-3)->edge = mesh->getFace(i)->edge->previous;

        // Neuf nouvelles demi-arêtes créées
        mesh->getEdge(mesh->getEdgeCount()-1)->face = mesh->getFace(mesh->getFaceCount()-1);
        mesh->getEdge(mesh->getEdgeCount()-2)->face = mesh->getFace(mesh->getFaceCount()-1);
        mesh->getEdge(mesh->getEdgeCount()-3)->face = mesh->getFace(mesh->getFaceCount()-2);
        mesh->getEdge(mesh->getEdgeCount()-4)->face = mesh->getFace(mesh->getFaceCount()-2);
        mesh->getEdge(mesh->getEdgeCount()-5)->face = mesh->getFace(mesh->getFaceCount()-3);
        mesh->getEdge(mesh->getEdgeCount()-6)->face = mesh->getFace(mesh->getFaceCount()-3);
        mesh->getEdge(mesh->getEdgeCount()-7)->face = mesh->getFace(i);
        mesh->getEdge(mesh->getEdgeCount()-8)->face = mesh->getFace(i);
        mesh->getEdge(mesh->getEdgeCount()-9)->face = mesh->getFace(i);

        mesh->getEdge(mesh->getEdgeCount()-1)->next = mesh->getEdge(mesh->getEdgeCount()-2);
        mesh->getEdge(mesh->getEdgeCount()-2)->next = mesh->getFace(i)->edge;
        mesh->getEdge(mesh->getEdgeCount()-3)->next = mesh->getEdge(mesh->getEdgeCount()-4);
        mesh->getEdge(mesh->getEdgeCount()-4)->next = mesh->getFace(i)->edge->next;
        mesh->getEdge(mesh->getEdgeCount()-5)->next = mesh->getEdge(mesh->getEdgeCount()-6);
        mesh->getEdge(mesh->getEdgeCount()-6)->next = mesh->getFace(i)->edge->previous;
        mesh->getEdge(mesh->getEdgeCount()-7)->next = mesh->getEdge(mesh->getEdgeCount()-8);
        mesh->getEdge(mesh->getEdgeCount()-8)->next = mesh->getEdge(mesh->getEdgeCount()-9);
        mesh->getEdge(mesh->getEdgeCount()-9)->next = mesh->getEdge(mesh->getEdgeCount()-7);

        mesh->getEdge(mesh->getEdgeCount()-1)->previous = mesh->getFace(i)->edge;
        mesh->getEdge(mesh->getEdgeCount()-2)->previous = mesh->getEdge(mesh->getEdgeCount()-1);
        mesh->getEdge(mesh->getEdgeCount()-3)->previous = mesh->getFace(i)->edge->next;
        mesh->getEdge(mesh->getEdgeCount()-4)->previous = mesh->getEdge(mesh->getEdgeCount()-3);
        mesh->getEdge(mesh->getEdgeCount()-5)->previous = mesh->getFace(i)->edge->previous;
        mesh->getEdge(mesh->getEdgeCount()-6)->previous = mesh->getEdge(mesh->getEdgeCount()-5);
        mesh->getEdge(mesh->getEdgeCount()-7)->previous = mesh->getEdge(mesh->getEdgeCount()-9);
        mesh->getEdge(mesh->getEdgeCount()-8)->previous = mesh->getEdge(mesh->getEdgeCount()-7);
        mesh->getEdge(mesh->getEdgeCount()-9)->previous = mesh->getEdge(mesh->getEdgeCount()-8);

        mesh->getEdge(mesh->getEdgeCount()-1)->opposite = mesh->getFace(i)->edge->next->opposite;
        mesh->getEdge(mesh->getEdgeCount()-2)->opposite = mesh->getEdge(mesh->getEdgeCount()-7);
        mesh->getEdge(mesh->getEdgeCount()-3)->opposite = mesh->getFace(i)->edge->previous->opposite;
        mesh->getEdge(mesh->getEdgeCount()-4)->opposite = mesh->getEdge(mesh->getEdgeCount()-8);
        mesh->getEdge(mesh->getEdgeCount()-5)->opposite = mesh->getFace(i)->edge->opposite;
        mesh->getEdge(mesh->getEdgeCount()-6)->opposite = mesh->getEdge(mesh->getEdgeCount()-9);
        mesh->getEdge(mesh->getEdgeCount()-7)->opposite = mesh->getEdge(mesh->getEdgeCount()-2);
        mesh->getEdge(mesh->getEdgeCount()-8)->opposite = mesh->getEdge(mesh->getEdgeCount()-4);
        mesh->getEdge(mesh->getEdgeCount()-9)->opposite = mesh->getEdge(mesh->getEdgeCount()-6);

        mesh->getEdge(mesh->getEdgeCount()-1)->vertex = v2;
        mesh->getEdge(mesh->getEdgeCount()-2)->vertex = v1;
        mesh->getEdge(mesh->getEdgeCount()-3)->vertex = v3;
        mesh->getEdge(mesh->getEdgeCount()-4)->vertex = v2;
        mesh->getEdge(mesh->getEdgeCount()-5)->vertex = v1;
        mesh->getEdge(mesh->getEdgeCount()-6)->vertex = v3;
        mesh->getEdge(mesh->getEdgeCount()-7)->vertex = v2;
        mesh->getEdge(mesh->getEdgeCount()-8)->vertex = v3;
        mesh->getEdge(mesh->getEdgeCount()-9)->vertex = v1;

        // Mise à jour des sommets de la face courante
        mesh->getFace(i)->edge->vertex->outgoing = mesh->getEdge(mesh->getEdgeCount()-1);
        mesh->getFace(i)->edge->next->vertex->outgoing = mesh->getEdge(mesh->getEdgeCount()-3);
        mesh->getFace(i)->edge->previous->vertex->outgoing = mesh->getEdge(mesh->getEdgeCount()-5);

        // Mise à jour des demi-arêtes opposées croisées
        if(mesh->getFace(i)->edge->next == mesh->getFace(i)->edge->next->opposite->previous->opposite->previous->opposite->previous->opposite) {
            mesh->getFace(i)->edge->next->opposite->opposite = mesh->getEdge(mesh->getEdgeCount()-1);
            mesh->getFace(i)->edge->next->opposite = mesh->getFace(i)->edge->next->opposite->previous->opposite->previous->opposite->previous;
        }
        if(mesh->getFace(i)->edge->previous == mesh->getFace(i)->edge->previous->opposite->previous->opposite->previous->opposite->previous->opposite) {
            mesh->getFace(i)->edge->previous->opposite->opposite = mesh->getEdge(mesh->getEdgeCount()-3);
            mesh->getFace(i)->edge->previous->opposite = mesh->getFace(i)->edge->previous->opposite->previous->opposite->previous->opposite->previous;
        }
        if(mesh->getFace(i)->edge == mesh->getFace(i)->edge->opposite->previous->opposite->previous->opposite->previous->opposite) {
            mesh->getFace(i)->edge->opposite->opposite = mesh->getEdge(mesh->getEdgeCount()-5);
            mesh->getFace(i)->edge->opposite = mesh->getFace(i)->edge->opposite->previous->opposite->previous->opposite->previous;
        }

        // Mise à jour des demi-arêtes de la face courante
        mesh->getFace(i)->edge->previous->face = mesh->getFace(mesh->getFaceCount()-3);
        mesh->getFace(i)->edge->previous->next = mesh->getEdge(mesh->getEdgeCount()-5);
        mesh->getFace(i)->edge->previous->previous = mesh->getEdge(mesh->getEdgeCount()-6);

        mesh->getFace(i)->edge->next->face = mesh->getFace(mesh->getFaceCount()-2);
        mesh->getFace(i)->edge->next->next = mesh->getEdge(mesh->getEdgeCount()-3);
        mesh->getFace(i)->edge->next->previous = mesh->getEdge(mesh->getEdgeCount()-4);

        mesh->getFace(i)->edge->face = mesh->getFace(mesh->getFaceCount()-1);
        mesh->getFace(i)->edge->next = mesh->getEdge(mesh->getEdgeCount()-1);
        mesh->getFace(i)->edge->previous = mesh->getEdge(mesh->getEdgeCount()-2);

        // Mise à jour de la face i
        mesh->getFace(i)->edge = mesh->getEdge(mesh->getEdgeCount()-7);
    }
}

void MeshProcessing::decimate(Mesh *mesh) {
    QVector<Face*> seen;

    for(int i=0 ; i < mesh->getFaceCount() ; ++i) {
        if(!seen.contains(mesh->getFace(i))) {
            QVector<QVector3D> vertices;
            vertices.resize(6);

            vertices[0] = mesh->getFace(i)->edge->vertex->coords;
            vertices[1] = mesh->getFace(i)->edge->next->opposite->next->vertex->coords;
            vertices[2] = mesh->getFace(i)->edge->next->vertex->coords;
            vertices[3] = mesh->getFace(i)->edge->previous->opposite->next->vertex->coords;
            vertices[4] = mesh->getFace(i)->edge->previous->vertex->coords;
            vertices[5] = mesh->getFace(i)->edge->opposite->next->vertex->coords;

            QVector<QVector3D> edges;
            edges.resize(6);
            for(int j=0 ; j < 6 ; ++j) { edges[j] = vertices[(j+1)%6] - vertices[j]; }

            // Test des angles plans
            bool ok = (QVector3D::dotProduct(edges[5], edges[0]) / (edges[1].length() * edges[2].length()) > M_PI / 8
                    && QVector3D::dotProduct(edges[1], edges[2]) / (edges[1].length() * edges[2].length()) > M_PI / 8
                    && QVector3D::dotProduct(edges[3], edges[4]) / (edges[1].length() * edges[2].length()) > M_PI / 8);

            QVector<QVector3D> normals;
            normals.resize(3);

            normals[0] = QVector3D::normal(vertices[1], vertices[0], vertices[2]).normalized();
            normals[1] = QVector3D::normal(vertices[3], vertices[2], vertices[4]).normalized();
            normals[2] = QVector3D::normal(vertices[5], vertices[4], vertices[0]).normalized();

            // Test des angles dièdres
            ok = ok && (QVector3D::dotProduct(normals[0], normals[2]) > M_PI / 8
                    && QVector3D::dotProduct(normals[1], normals[0]) > M_PI / 8
                    && QVector3D::dotProduct(normals[2], normals[1]) > M_PI / 8);

            // Fusion des arêtes
            if(ok) {
                seen.push_back(mesh->getFace(i));
                seen.push_back(mesh->getFace(i)->edge->opposite->face);
                seen.push_back(mesh->getFace(i)->edge->next->opposite->face);
                seen.push_back(mesh->getFace(i)->edge->previous->opposite->face);

                mesh->mergeEdge(vertices[5], vertices[0], vertices[1]);
                mesh->mergeEdge(vertices[1], vertices[2], vertices[3]);
                mesh->mergeEdge(vertices[3], vertices[4], vertices[5]);
            }
        }
    }
}

bool MeshProcessing::subdivideAuto(Mesh *mesh, float maxEdgeLength) {
    bool result = false;
    QVector3D p1, p2;
    int size = mesh->getEdgeCount();

    for(int i=0 ; i < size ; ++i) {
        p1 = mesh->getEdge(i)->previous->vertex->coords;
        p2 = mesh->getEdge(i)->vertex->coords;
        if(p1.distanceToPoint(p2) > maxEdgeLength) {
            mesh->cutEdge(p1, p2);
            result = true;
        }
    }

    return result;
}

bool MeshProcessing::decimateAuto(Mesh *mesh, float minEdgeLength) {
    bool result = false;
    QVector3D Ori, OA, OB;
    float angle;

    QVector<QVector3D> neighbours, seen;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        Ori = mesh->getVertex(i)->coords;

        if(!seen.contains(Ori)) {

            neighbours.clear();
            neighbours = mesh->getNeighbours(Ori, 1);

            int j = 0;
            while(j < neighbours.size()-1) {

                int k = j+1;
                while(k < neighbours.size()) {

                    if(j != k && neighbours[j] != Ori && neighbours[k] != Ori) {
                        OA = Ori - neighbours[j]; // j to origin
                        OB = neighbours[k] - Ori; // origin to k

                        if(OA.length() < minEdgeLength && OB.length() < minEdgeLength) {
                            angle = QVector3D::dotProduct(OA, OB) / (OA.length() * OB.length()); // rad

                            if(angle < M_PI / 8) { // 22.5 deg
                                if(mesh->mergeEdge(neighbours[j], Ori, neighbours[k])) {
                                    result = true;

                                    for(int l=0 ; l < neighbours.size() ; ++l) {
                                        seen.push_back(neighbours[l]); // including Ori
                                    }
                                    j = k = neighbours.size();
                                }
                            }
                        }
                    }
                    ++k;
                }
                ++j;
            }
        }
    }

    return result;
}

void MeshProcessing::scale(Mesh *mesh, QVector3D coef) {
    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->getVertex(i)->coords -= mesh->getCenter()*coef + mesh->getCenter();
    }
}
