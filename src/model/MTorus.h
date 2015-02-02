#ifndef MTORUS_H
#define MTORUS_H

#include "model/Model.h"

using namespace std;

class MTorus : public Model
{
public:
    MTorus();
    void initializeGL();

private:
    float m_radius1;
    float m_radius2;
};

#endif // MTORUS_H
