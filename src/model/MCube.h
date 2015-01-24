#ifndef MCUBE_H
#define MCUBE_H

#include "model/Model.h"

using namespace std;

class MCube : public Model
{
    Q_OBJECT

public:
    void initializeGL();
    void paintGL();

private:
    int vertices_by_x;
    int vertices_by_y;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_y;
    int quads_by_z;
};

#endif // MCUBE_H
