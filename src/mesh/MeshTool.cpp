#include "MeshTool.h"
#include "Mesh.h"

// GLOBAL TOOLS

void MeshTool::gtmove(Mesh *mesh, QVector3D move) {
    //qDebug() << "GTMove action";

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->moveVertex(i ,move);
    }

    mesh->setCenter(mesh->getCenter() + move);
}

void MeshTool::gtrotate(Mesh *mesh, QVector3D move) {
    //qDebug() << "GTRotate action";

    QVector3D center = mesh->getCenter();
    QVector3D currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = rotateXYZ(mesh->getCoords(i) - center, move);
        currentPoint.setZ(-currentPoint.z());
        mesh->setCoords(i, currentPoint + center);
    }
}

void MeshTool::gtscale(Mesh *mesh, QVector3D move) {
    //qDebug() << "GTScale action";

    float coef = 1.0 - move.y() / 200.;
    QVector3D center = mesh->getCenter();

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->setCoords(i, (mesh->getCoords(i) - center) * coef + center);
    }
}


// LOCAL TOOLS

void MeshTool::ltadd(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers) {
    //qDebug() << "LTAdd action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size() ; ++i) {
            mesh->moveVertex(vertices[i], normal * strength / 2.);
        }
    }
}

void MeshTool::ltinflate(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers) {
    //qDebug() << "LTInflate action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;
        QVector3D vector;

        for(int i=0 ; i < vertices.size() ; ++i) {
            vector = vertices[i] - position; // Vecteur à projeter sur le plan du brush
            vector -= QVector3D::dotProduct(normal, vector) * normal; // Projection
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], (normal + vector) * coef * strength);
        }
    }
}

void MeshTool::ltmove(Mesh *mesh, QPoint last_position, QVector3D move, float brushSize) {
    //qDebug() << "LTMove action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;

        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], move * coef);
        }
    }
}

void MeshTool::ltpinch(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers) {
    //qDebug() << "LTPinch action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        QVector3D normal = mesh->getNormal(position);
        if(modifiers & Qt::ShiftModifier) { normal = -normal; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        float coef;
        QVector3D vector;

        for(int i=0 ; i < vertices.size() ; ++i) {
            vector = vertices[i] - position; // Vecteur à projeter sur le plan du brush
            vector -= QVector3D::dotProduct(normal, vector) * normal; // Projection
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], (normal * strength - vector) * coef * strength);
        }
    }
}

void MeshTool::ltsmooth(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers) {
    //qDebug() << "LTSmooth action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        float tmp_strength = strength;
        if(modifiers & Qt::ShiftModifier) { tmp_strength *= 20.; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        QVector3D mean;
        for(int i=0 ; i < vertices.size() ; ++i) {
            mean += vertices[i];
        }
        mean /= vertices.size();

        QVector<QVector3D> neighbours, means; means.resize(vertices.size());


        // Calcul des moyennes des voisins
        for(int i=0 ; i < vertices.size() ; ++i) {
            neighbours.clear();
            neighbours = mesh->getNeighbours(vertices[i], 1);

            means[i] = QVector3D(0,0,0);
            for(int j=0 ; j < neighbours.size() ; ++j) {
                if(neighbours[j] != vertices[i]) {
                    means[i] += neighbours[j];
                }
            }
            means[i] /= neighbours.size() - 1;
        }

        // Lissage par les moyennes
        float coef;
        for(int i=0 ; i < vertices.size() ; ++i) {
            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], (means[i] - vertices[i]) * coef * tmp_strength);
        }
    }
}


// OTHERS

void MeshTool::subdivideAuto(Mesh *mesh, QPoint last_position, float brushSize) {
    //qDebug() << "SubdivideAuto action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        QVector<QVector<QVector3D> > neighbours; neighbours.resize(vertices.size());

        for(int i=0 ; i < vertices.size() ; ++i) {
            neighbours[i] = mesh->getNeighbours(vertices[i], 1);
        }

        // Longueur moyenne entre les points
        float maxEdgeLength = 0;
        for(int i=0 ; i < vertices.size()-1 ; ++i) {
            for(int j=0 ; j < neighbours[i].size() ; ++j) {
                maxEdgeLength += vertices[i].distanceToPoint(neighbours[i][j]);
            }
        }
        maxEdgeLength /= vertices.size() * 2*brushSize;

        // Subdivision automatique
        for(int i=0 ; i < vertices.size() ; ++i) {
            for(int j=0 ; j < neighbours[i].size() ; ++j) {
                if(vertices[i].distanceToPoint(neighbours[i][j]) > maxEdgeLength) {
                    mesh->cutEdge(vertices[i], neighbours[i][j]);
                }
            }
        }
    }
}

void MeshTool::decimateAuto(Mesh *mesh, QPoint last_position, float brushSize) {
    //qDebug() << "DecimateAuto action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);
        QVector<QVector<QVector3D> > neighbours; neighbours.resize(vertices.size());

        for(int i=0 ; i < vertices.size() ; ++i) {
            neighbours[i] = mesh->getNeighbours(vertices[i], 1);
        }

        // Longueur moyenne entre les points
        float minEdgeLength = 0;
        for(int i=0 ; i < vertices.size()-1 ; ++i) {
            for(int j=0 ; j < neighbours[i].size() ; ++j) {
                minEdgeLength += vertices[i].distanceToPoint(neighbours[i][j]);
            }
        }
        minEdgeLength /= vertices.size() * 2*brushSize;

        // Decimation automatique
        QVector3D OA, OB;
        QVector<QVector3D> seen;
        float angle;

        for(int i=0 ; i < vertices.size() ; ++i) {
            if(!seen.contains(vertices[i])) {

                // Tester si l'ensemble de faces est plutôt plat
                bool ok = true;
                OA = QVector3D::normal(neighbours[i][0], vertices[i], neighbours[i][1]).normalized();
                for(int l=1 ; l < neighbours[i].size() ; ++l) {
                    OB = QVector3D::normal(neighbours[i][l], vertices[i], neighbours[i][(l+1)%neighbours[i].size()]).normalized();
                    angle = QVector3D::dotProduct(OA, OB);
                    ok = ok && (angle < M_PI/8);
                }

                if(ok) {
                    bool oa=false, ob=false;
                    int j=0;
                    while(j < neighbours[i].size()) {
                        if(neighbours[i][j] != vertices[i]) {
                            if(!oa) {
                                OA = neighbours[i][j] - vertices[i];
                                if(OA.length() < minEdgeLength) {
                                    OA = neighbours[i][j];
                                    oa = true;
                                }
                            }
                            else if(!ob) {
                                OB = vertices[i] - neighbours[i][j];
                                if(OB.length() < minEdgeLength && QVector3D::dotProduct((OA-vertices[i]).normalized(), -OB.normalized()) < M_PI / 8) {
                                    OB = neighbours[i][j];
                                    ob = true;
                                }
                            }

                            if(oa && ob) {
                                if(mesh->mergeEdge(OA, vertices[i], OB)) {
                                    j = neighbours[i].size();
                                    for(int k=0 ; k < neighbours[i].size() ; ++k) {
                                        seen.push_back(neighbours[i][k]);
                                    }
                                }
                            }
                        }
                        ++j;
                    }
                }
            }
        }
    }
}
