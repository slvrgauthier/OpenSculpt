#include "tool/GTRotate.h"
#include "model/func.h"

void GTRotate::action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot)
{
    float dx = current_position.x() - last_position.x(), dy = current_position.y() - last_position.y();
    float x,y,z, x_,y_,z_;
    QVector3D currentPoint, center = model->getCenter();

    for(int i=0 ; i < model->getSize() ; ++i) {
        currentPoint = model->getVertex(i);

        x = currentPoint.x() - center.x(), y = currentPoint.y() - center.y(), z = currentPoint.z() - center.z();
        //Rotation autour de X
        x_ = x, y_ = y*cosd(dy) - z*sind(dy), z_ = y*sind(dy) + z*cosd(dy);
        //Rotation autour de Y
        x = x_*cosd(dx)+z_*sind(dx), y = y_, z = z_*cosd(dx)-x_*sind(dx);

        currentPoint.setX(x + center.x());
        currentPoint.setY(y + center.y());
        currentPoint.setZ(z + center.z());
        model->setVertex(i, currentPoint);
    }
    model->update();
}
