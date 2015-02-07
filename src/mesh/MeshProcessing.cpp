#include "MeshProcessing.h"

MeshProcessing::MeshProcessing() {  }
MeshProcessing::~MeshProcessing() {  }

void MeshProcessing::subdivide(Mesh *mesh) {

    int size = mesh->getFaceCount();

    //mesh->resizeFace(4 * size);
    //mesh->resizeEdge(mesh->getEdgeCount() + 9 * size);
    //mesh->resizeVertex(mesh->getVertexCount() + 3 * size);

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
    int size = mesh->getFaceCount() / 4;

    for(int i=0 ; i < size ; ++i) {
        HalfEdge *e1, *e2, *e3;

        // Initialiser les trois demi-arêtes
        e1 = mesh->getFace(i)->edge->opposite->next;
        e2 = mesh->getFace(i)->edge->next->opposite->next;
        e3 = mesh->getFace(i)->edge->previous->opposite->next;

        // Supprimer les trois faces décimées
        delete e1->face;
        delete e2->face;
        delete e3->face;

        e1->face = mesh->getFace(i);
        e2->face = mesh->getFace(i);
        e3->face = mesh->getFace(i);

        // Supprimer les six demi-arêtes centrales
        delete mesh->getFace(i)->edge->previous->opposite;
        delete mesh->getFace(i)->edge->previous;
        delete mesh->getFace(i)->edge->next->opposite;
        delete mesh->getFace(i)->edge->next;
        delete mesh->getFace(i)->edge->opposite;
        delete mesh->getFace(i)->edge;

        // Supprimer les trois vertices décimés
        if(e3->next->opposite == e1->opposite) {
            // Le point n'est plus lié en face
            delete e3->next->vertex;
            e3->next->opposite->opposite = e1;
        }
        else {
            // Le point est lié en face
            e1->opposite = e3->next->opposite;
        }
        if(e1->next->opposite == e2->opposite) {
            // Le point n'est plus lié en face
            delete e1->next->vertex;
            e1->next->opposite->opposite = e2;
        }
        else {
            // Le point est lié en face
            e2->opposite = e1->next->opposite;
        }
        if(e2->next->opposite == e3->opposite) {
            // Le point n'est plus lié en face
            delete e2->next->vertex;
            e2->next->opposite->opposite = e3;
        }
        else {
            // Le point est lié en face
            e3->opposite = e2->next->opposite;
        }

        // Supprimer les trois demi-arêtes
        delete e1->next;
        delete e2->next;
        delete e3->next;

        // Etendre la face centrale vers l'extérieur
        mesh->getFace(i)->edge = e1;
        mesh->getFace(i)->edge->next = e2;
        mesh->getFace(i)->edge->previous = e3;

        e1->previous = e3;
        e1->next = e2;
        e2->previous = e1;
        e2->next = e3;
        e3->previous = e2;
        e3->next = e1;
    }
}

void MeshProcessing::subdivideAuto(Mesh *mesh, float maxEdgeLength) {  }

void MeshProcessing::decimateAuto(Mesh *mesh, float minEdgeLength) {  }

void MeshProcessing::scale(Mesh *mesh, QVector3D coef) {
    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->getVertex(i)->coords -= mesh->getCenter()*coef + mesh->getCenter();
    }
}
