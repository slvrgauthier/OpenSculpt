#ifndef MTORUS_H
#define MTORUS_H

#include "model/Model.h"

using namespace std;

class MTorus : public Model
{
public:
    void initializeGL();
    void paintGL();
};

#endif // MTORUS_H
