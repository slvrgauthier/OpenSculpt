#ifndef GTROTATE_H
#define GTROTATE_H

#include "tool/Tool.h"

class GTRotate : public Tool
{
public:
    virtual void action(Model *model, QVector3D position, int dx, int dy);
};

#endif // GTROTATE_H
