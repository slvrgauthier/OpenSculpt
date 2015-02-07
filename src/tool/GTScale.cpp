#include "tool/GTScale.h"

void GTScale::action(Mesh *mesh, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "GTScale action";

    float coef = 1.0 - (current_position.y() - last_position.y()) / 200.;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        mesh->getVertex(i)->coords = (mesh->getVertex(i)->coords - mesh->getCenter())*coef + mesh->getCenter();
    }
}
