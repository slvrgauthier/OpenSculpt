#ifndef LTPINCH_H
#define LTPINCH_H

#include "tool/Tool.h"

class LTPinch : public Tool
{
public:
    void action(Model *model, QVector3D position, QVector3D move);
};

#endif // LTPINCH_H
