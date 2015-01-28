#ifndef MSPHERE_H
#define MSPHERE_H

#include "model/Model.h"

using namespace std;

class MSphere : public Model
{
public:
    void initializeGL();
    void paintGL();
};

#endif // MSPHERE_H
