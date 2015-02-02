#ifndef GTSCALE_H
#define GTSCALE_H

#include "tool/Tool.h"

class GTScale : public Tool
{
public:
    void action(Model *model, QPoint last_position, QPoint current_position, float distance, float x_rot, float y_rot, float z_rot);
};

#endif // GTSCALE_H
