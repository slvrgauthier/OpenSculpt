#ifndef MCUBE_H
#define MCUBE_H

#include "model/Model.h"

using namespace std;

class MCube : public Model
{
public:
    MCube();
    void initializeGL();

public:
    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);

    float getWidth() const;
    float getDepth() const;
    float getHeight() const;

private:
    float m_width;
    float m_height;
    float m_depth;
};

#endif // MCUBE_H
