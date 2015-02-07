#ifndef LTADD_H
#define LTADD_H

#include "tool/Tool.h"

class LTAdd : public Tool
{
public:
    void action(Mesh *mesh, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // LTADD_H
