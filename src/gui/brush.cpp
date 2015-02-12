#include "brush.h"

Brush::Brush() {}

Brush::~Brush() {}

void Brush::paintGL(QPoint mouse) {

    QVector3D position = get3Dposition(mouse); // Position dans le repère scène

    if(!position.isNull()) {

        glBegin(GL_LINE_LOOP);
            float alpha;
            for (int i=0; i < 16; ++i) {
                alpha = i * 360 / 16.;
                glVertex3f(position.x() + cosd(alpha)*m_size, position.y() + sind(alpha)*m_size, position.z());
            }
        glEnd();
    }
    else {

    }
}

float Brush::getSize() const { return m_size; }

void Brush::setSize(float size) { m_size = size; }

float Brush::getStrength() const { return m_strength; }

void Brush::setStrength(float strength) { m_strength = strength; }
