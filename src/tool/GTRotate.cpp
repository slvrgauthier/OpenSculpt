#include "tool/GTRotate.h"

void GTRotate::action(Mesh *mesh, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "GTRotate action";

    float dx = current_position.x() - last_position.x(), dy = current_position.y() - last_position.y();
    float x,y,z, x_,y_,z_;
    QVector3D center = mesh->getCenter();
    Vertex *currentPoint;

    for(int i=0 ; i < mesh->getVertexCount() ; ++i) {
        currentPoint = mesh->getVertex(i);

        x = currentPoint->coords.x() - center.x(), y = currentPoint->coords.y() - center.y(), z = currentPoint->coords.z() - center.z();
        //Rotation autour de X
        x_ = x, y_ = y*cosd(dy) - z*sind(dy), z_ = y*sind(dy) + z*cosd(dy);
        //Rotation autour de Y
        x = x_*cosd(dx)+z_*sind(dx), y = y_, z = z_*cosd(dx)-x_*sind(dx);

        currentPoint->coords.setX(x + center.x());
        currentPoint->coords.setY(y + center.y());
        currentPoint->coords.setZ(z + center.z());
        mesh->setVertex(i, currentPoint);
    }
}
