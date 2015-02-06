#include "tool/GTMove.h"

void GTMove::action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot)
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

    for(int i=0 ; i < model->getSize() ; ++i) {
        model->setVertex(i, model->getVertex(i) + move);
    }

    model->setCenter(model->getCenter() + move);

    model->update();
}
