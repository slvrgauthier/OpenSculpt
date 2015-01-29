#ifndef LTSMOOTH_H
#define LTSMOOTH_H

#include "tool/Tool.h"

class LTSmooth : public Tool
{
public:
    void action(Model *model, QVector3D position, QVector3D move);
};

#endif // LTSMOOTH_H
