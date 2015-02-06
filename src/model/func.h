/*
 * func.h
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
#include <cmath>
#include <QVector3D>
#include <QPoint>

/* cosinus and sinus with degrees */
#define cosd(x) (cos(fmod((x),360) * M_PI / 180))
#define sind(x) (sin(fmod((x),360) * M_PI / 180))

/* get 3D position of the pixel under the cursor */
QVector3D getGLpos(QPoint mouse);

#endif // FUNCTIONS_H
