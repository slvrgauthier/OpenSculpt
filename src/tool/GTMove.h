#ifndef GTMOVE_H
#define GTMOVE_H

#include "tool/Tool.h"

class GTMove : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // GTMOVE_H
