#include "tool/LTMove.h"
#include <QDebug>

void LTMove::action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "LTMove action";

    model->getSize();last_position.isNull();current_position.isNull();if(distance==x_rot&&y_rot==z_rot){};
}
