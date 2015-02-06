#ifndef MCONE_H
#define MCONE_H

#include "model/Model.h"

using namespace std;

class MCone : public Model
{
public:
    MCone();
    void initializeGL();
    void setRadiusDown(float radius);
    void setRadiusUP(float radius);
    void setHeight(float height);
private:
    float m_radius1;
    float m_radius2;
    float m_height;
};

#endif // MCONE_H
