#ifndef GTSCALE_H
#define GTSCALE_H

#include "tool/Tool.h"

class GTScale : public Tool
{
public:
    void action(Model *model, QVector3D position, int dx, int dy);
};

#endif // GTSCALE_H
