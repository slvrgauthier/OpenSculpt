#ifndef LTMOVE_H
#define LTMOVE_H

#include "tool/Tool.h"

class LTMove : public Tool
{
public:
    void action(Model *model, QVector3D position, float dx, float dy);
};

#endif // LTMOVE_H
