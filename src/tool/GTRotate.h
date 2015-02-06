#ifndef GTROTATE_H
#define GTROTATE_H

#include "tool/Tool.h"

class GTRotate : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // GTROTATE_H
