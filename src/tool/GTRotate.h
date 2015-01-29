#ifndef GTROTATE_H
#define GTROTATE_H

#include "tool/Tool.h"

class GTRotate : public Tool
{
public:
    virtual void action(Model *model, QVector3D position, float dx, float dy);
};

#endif // GTROTATE_H
