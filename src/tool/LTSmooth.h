#ifndef LTSMOOTH_H
#define LTSMOOTH_H

#include "tool/Tool.h"

class LTSmooth : public Tool
{
public:
    void action(Model *model, QVector3D position, float dx, float dy);
};

#endif // LTSMOOTH_H
