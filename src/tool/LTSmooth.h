#ifndef LTSMOOTH_H
#define LTSMOOTH_H

#include "tool/Tool.h"

class LTSmooth : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // LTSMOOTH_H
