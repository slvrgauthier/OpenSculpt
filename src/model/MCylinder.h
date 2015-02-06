#ifndef MCYLINDER_H
#define MCYLINDER_H

#include "model/Model.h"

using namespace std;

class MCylinder : public Model
{
public:
    MCylinder();
    void initializeGL();

public:
    void setRadius(float radius);
    void setHeight(float height);

private:
    float m_radius;
    float m_height;
};

#endif // MCYLINDER_H
