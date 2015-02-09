#include "functions.h"

QVector3D rotateXYZ(QVector3D vector, QVector3D rotation) {
    float x, y, z, x_ = vector.x(), y_ = vector.y(), z_ = vector.z();

    //Rotation autour de X
    x = x_, y = y_ * cosd(rotation.x()) - z_ * sind(rotation.x()), z = y_ * sind(rotation.x()) + z_ * cosd(rotation.x());

    //Rotation autour de Y
    x_ = x * cosd(rotation.y()) + z * sind(rotation.y()), y_ = y, z_ = z * cosd(rotation.y()) - x * sind(rotation.y());

    //Rotation autour de Z
    x = x_ * cosd(rotation.z()) - y_ * sind(rotation.z()), y = x_ * sind(rotation.z()) + y_ * cosd(rotation.z()), z = z_;

    return QVector3D(x, y, -z);
}

QVector3D get3Dposition(QPoint mouse)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    float x = mouse.x(), y = mouse.y();
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;

    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    if(winZ == 1 || winZ == 0) {
        return QVector3D();
    }
    else {
        gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
        return QVector3D(posX, posY, posZ); // position 3D du pixel touché
    }
}

bool inTriangle(QVector3D p, QVector3D p0, QVector3D p1, QVector3D p2) {

    QVector3D l1, l2, l3;
    float angle;
    float dot1, dot2, dot3;

    l1 = p0 - p;
    l2 = p1 - p;
    l3 = p2 - p;

    l1.normalize();
    l2.normalize();
    l3.normalize();

    dot1 = QVector3D::dotProduct(l1, l2);
    dot2 = QVector3D::dotProduct(l2, l3);
    dot3 = QVector3D::dotProduct(l3, l1);

    angle = acos(dot1) + acos(dot2) + acos(dot3);

    return (angle < 2.1*M_PI && angle > 1.9*M_PI);
}
