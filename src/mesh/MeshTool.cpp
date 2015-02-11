#include "MeshTool.h"
#include "Mesh.h"

// GLOBAL TOOLS

void MeshTool::gtmove(Mesh *mesh, QVector3D move) {
    qDebug() << "GTMove action";

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->moveVertex(i ,move);
    }

    mesh->setCenter(mesh->getCenter() + move);
}

void MeshTool::gtrotate(Mesh *mesh, QVector3D move) {
    qDebug() << "GTRotate action";

    QVector3D center = mesh->getCenter();
    QVector3D currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = rotateXYZ(mesh->getCoords(i) - center, move);
        currentPoint.setZ(-currentPoint.z());
        mesh->setCoords(i, currentPoint + center);
    }
}

void MeshTool::gtscale(Mesh *mesh, QVector3D move) {
    qDebug() << "GTScale action";

    float coef = 1.0 - move.y() / 200.;
    QVector3D center = mesh->getCenter();

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->setCoords(i, (mesh->getCoords(i) - center) * coef + center);
    }
}


// LOCAL TOOLS

void MeshTool::ltadd(Mesh *mesh, QPoint last_position, float brushSize, float strength, Qt::KeyboardModifiers modifiers) {
    qDebug() << "LTAdd action";

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
    qDebug() << "LTInflate action";

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
    qDebug() << "LTMove action";

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
    qDebug() << "LTPinch action";

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
    qDebug() << "LTSmooth action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {
        float tmp_strength = strength;
        if(modifiers & Qt::ShiftModifier) { tmp_strength *= 20.; }

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        QVector3D normal = mesh->getNormal(position);

        QVector3D mean;
        for(int i=0 ; i < vertices.size() ; ++i) {
            mean += vertices[i];
        }
        mean /= vertices.size();

        QVector<QVector3D> neighbours, means; means.resize(vertices.size());


        // Calcul des moyennes des voisins
        for(int i=0 ; i < vertices.size() ; ++i) {

            coef = std::max(0.f, 1 - vertices[i].distanceToPoint(position) / brushSize);
            mesh->moveVertex(vertices[i], -mean * coef * strength);
        }
    }

        /*QVector<QVector3D> norm_comps; norm_comps.resize(vertices.size());
        float dot;
=======
            neighbours.clear();
            neighbours = mesh->getNeighbours(vertices[i], 1);
>>>>>>> FETCH_HEAD

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
    }*/
}


// OTHERS

void MeshTool::subdivideAuto(Mesh *mesh, QPoint last_position, float brushSize, float maxEdgeLength) {
    qDebug() << "SubdivideAuto action";

    QVector3D position = get3Dposition(last_position); // Position dans le repère scène

    if(!position.isNull()) {

        QVector<QVector3D> vertices = mesh->getVertices(position, brushSize);

        for(int i=0 ; i < vertices.size()-1 ; ++i) {
            for(int j=i+1 ; j < vertices.size() ; ++j) {
                if(vertices[i].distanceToPoint(vertices[j]) > maxEdgeLength) {
                    mesh->cutEdge(vertices[i], vertices[j]);
                }
            }
        }
    }
}
