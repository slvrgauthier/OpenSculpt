#include "tool/GTScale.h"

void GTScale::action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "GTScale action";

    float dy = current_position.y() - last_position.y();

    model->scale(1.0-dy/200);
}
