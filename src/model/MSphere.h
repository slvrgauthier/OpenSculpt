#ifndef MSPHERE_H
#define MSPHERE_H

#include "model/Model.h"

using namespace std;

class MSphere : public Model
{
public:
    MSphere();
    void initializeGL();

private:
    float m_radius;
};

#endif // MSPHERE_H
