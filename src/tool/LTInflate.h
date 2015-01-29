#ifndef LTINFLATE_H
#define LTINFLATE_H

#include "tool/Tool.h"

class LTInflate : public Tool
{
public:
    void action(Model *model, QVector3D position, float dx, float dy);
};

#endif // LTINFLATE_H
