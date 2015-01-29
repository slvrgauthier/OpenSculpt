#ifndef LTINFLATE_H
#define LTINFLATE_H

#include "tool/Tool.h"

class LTInflate : public Tool
{
public:
    void action(Model *model, QVector3D position, int dx, int dy);
};

#endif // LTINFLATE_H
