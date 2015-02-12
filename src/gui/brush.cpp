#include "brush.h"

Brush::Brush() {}

Brush::~Brush() {}

void Brush::paintGL(QPoint mouse, Mesh *mesh) {

    GLfloat color[4] = {0., 1., 0., 1.};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);

    QVector3D position = get3Dposition(mouse); // Position dans le repère scène
    QVector<QVector3D> coords;

    if(!position.isNull() && mesh != NULL) {
        float alpha;
        for (int i=0; i < 16; ++i) {
            alpha = i * 360 / 16.;
            coords.push_back(QVector3D(cosd(alpha)*m_size, sind(alpha)*m_size, 0.));
        }

        QVector3D normal = mesh->getNormal(position);
        QVector3D currentPoint;

        // Rotation du brush selon la normale à la face
        for(int i=0 ; i < coords.size() ; ++i) {
            currentPoint = rotateXYZ(coords[i], QVector3D(normal.y()*90, normal.x()*90, 0));
            currentPoint.setZ(-currentPoint.z());
            coords[i] = currentPoint + position + normal * 0.1;
        }
    }

    glBegin(GL_LINE_LOOP);
        for(int i=0 ; i < coords.size() ; ++i) {
            glVertex3f(coords[i].x(), coords[i].y(), coords[i].z());
        }
    glEnd();
}

float Brush::getSize() const { return m_size; }

void Brush::setSize(float size) { m_size = size; }

float Brush::getStrength() const { return m_strength; }

void Brush::setStrength(float strength) { m_strength = strength; }
