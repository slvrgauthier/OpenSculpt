#ifndef MCUBE_H
#define MCUBE_H

#include "model/Model.h"

using namespace std;

class MCube : public Model
{
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

public slots:
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
};

#endif // MCUBE_H
