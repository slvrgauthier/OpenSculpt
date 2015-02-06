#include "tool/LTAdd.h"
#include <QDebug>

void LTAdd::action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot)
{
    qDebug() << "LTAdd action";

    model->getSize();last_position.isNull();current_position.isNull();if(distance==x_rot&&y_rot==z_rot&&brushSize==1){};
}
