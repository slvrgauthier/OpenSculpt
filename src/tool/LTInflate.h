#ifndef LTINFLATE_H
#define LTINFLATE_H

#include "tool/Tool.h"

class LTInflate : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // LTINFLATE_H
