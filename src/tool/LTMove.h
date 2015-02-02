#ifndef LTMOVE_H
#define LTMOVE_H

#include "tool/Tool.h"

class LTMove : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // LTMOVE_H
