#ifndef MCUBE_H
#define MCUBE_H

#include "model/Model.h"

using namespace std;

class MCube : public Model
{

public:
    MCube();
    void initializeGL();
    void paintGL();


private:
    float m_width;
    float m_height;
    float m_depth;

public slots:
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
};

#endif // MCUBE_H
