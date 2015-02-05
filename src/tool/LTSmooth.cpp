#include "tool/LTSmooth.h"
#include <QDebug>

void LTSmooth::action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "LTSmooth action";

    model->getSize();last_position.isNull();current_position.isNull();if(distance==x_rot&&y_rot==z_rot){};
}
