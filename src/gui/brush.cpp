#include "brush.h"

Brush::Brush() {}

Brush::~Brush() {}

void Brush::paintGL(QVector3D position) {

    //QVector3D position = QVector3D(last_position.x(),-last_position.y(),0);//get3Dposition(last_position); // Position dans le repère scène

    //if(!position.isNull()) {
        //QVector3D normal = mesh->getNormal(position);

        glBegin(GL_TRIANGLE_FAN);
            float alpha;
            for (int i=0; i < 16; ++i) {
                alpha = i * 360 / 16.;
                glVertex3f(position.x() + cosd(alpha)*m_size, position.y() + sind(alpha)*m_size, position.z());
            }
        glEnd();
    //}
}

float Brush::getSize() const { return m_size; }

void Brush::setSize(float size) { m_size = size; }
