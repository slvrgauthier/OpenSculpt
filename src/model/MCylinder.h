#ifndef MCYLINDER_H
#define MCYLINDER_H

#include "model/Model.h"

using namespace std;

class MCylinder : public Model
{
public:
    void initializeGL();
    void paintGL();
};

#endif // MCYLINDER_H
