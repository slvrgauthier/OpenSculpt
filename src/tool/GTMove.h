#ifndef GTMOVE_H
#define GTMOVE_H

#include "tool/Tool.h"

class GTMove : public Tool
{
public:
    void action(Model *model, QVector3D position, int dx, int dy);
};

#endif // GTMOVE_H
