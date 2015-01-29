#ifndef LTMOVE_H
#define LTMOVE_H

#include "tool/Tool.h"

class LTMove : public Tool
{
public:
    void action(Model *model, QVector3D position, QVector3D move);
};

#endif // LTMOVE_H
