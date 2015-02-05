#include "model/func.h"
#include "tool/GTMove.h"
#include <QDebug>

void GTMove::action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "GTMove action";

    float dx = current_position.x() - last_position.x(), dy = current_position.y() - last_position.y();
    float coef = distance / 900.0; // Compensation perspective

    float x,y,z, x_,y_,z_;
    //Rotation autour de X
    x_ = -dx, y_ = dy*cosd(x_rot), z_ = dy*sind(x_rot);
    //Rotation autour de Y
    x = x_*cosd(y_rot)+z_*sind(y_rot), y = y_, z = z_*cosd(y_rot)-x_*sind(y_rot);
    //Rotation autour de Z
    x_ = x*cosd(z_rot)-y*sind(z_rot), y_ = x*sind(z_rot)+y*cosd(z_rot), z_ = z;
    // Mise à l'échelle
    x = x_*coef, y = y_*coef, z = -z_*coef;

    QVector3D move(x,y,z); // Mouvement dans le repère scène

    QVector3D currentPoint;
    for(int i=0 ; i < model->getSize() ; ++i) {
        currentPoint = model->getVertex(i);
        currentPoint.setX(currentPoint.x()+move.x());
        currentPoint.setY(currentPoint.y()+move.y());
        currentPoint.setZ(currentPoint.z()+move.z());
        model->setVertex(i, currentPoint);
    }

    currentPoint = model->getCenter();
    currentPoint.setX(currentPoint.x()+move.x());
    currentPoint.setY(currentPoint.y()+move.y());
    currentPoint.setZ(currentPoint.z()+move.z());
    model->setCenter(currentPoint);

    model->update();
}
