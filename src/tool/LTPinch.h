#ifndef LTPINCH_H
#define LTPINCH_H

#include "tool/Tool.h"

class LTPinch : public Tool
{
public:
    void action(Model *model, QVector3D position, float dx, float dy);
};

#endif // LTPINCH_H
