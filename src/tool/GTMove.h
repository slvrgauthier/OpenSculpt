#ifndef GTMOVE_H
#define GTMOVE_H

#include "tool/Tool.h"

class GTMove : public Tool
{
public:
    void action(Model *model, QVector3D position, QVector3D move);
};

#endif // GTMOVE_H
