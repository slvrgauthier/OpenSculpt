/*
 * functions.h
 * @author : Team OpenSculpt
 *
 * This file gives some useful functions outside any class.
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #include <windows.h>
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <QVector3D>
#include <QPoint>
#include "mesh/Mesh.h"

/* cosinus and sinus with degrees */
#define cosd(x) (cos(fmod((x),360) * M_PI / 180))
#define sind(x) (sin(fmod((x),360) * M_PI / 180))

/* rotation of a QVector3D */
QVector3D rotateXYZ(QVector3D vector, QVector3D rotation);

/* get 3D position of the pixel under the cursor */
QVector3D get3Dposition(QPoint mouse);

/* test if a point p is in a triangle defined by p0, p1 and p2 */
bool inTriangle(QVector3D p, QVector3D p0, QVector3D p1, QVector3D p2);

#endif // FUNCTIONS_H
