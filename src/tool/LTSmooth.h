#ifndef LTSMOOTH_H
#define LTSMOOTH_H

#include "tool/Tool.h"

class LTSmooth : public Tool
{
public:
    void action(Mesh *mesh, QPoint last_position, QPoint current_position, int brushSize, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // LTSMOOTH_H
