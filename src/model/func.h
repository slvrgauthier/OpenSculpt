/*
 * func.h
 * @author : Team OpenSculpt
 *
 * This file gives some useful functions outside any class.
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdlib.h>
#include <cmath>

/* cosinus and sinus with degrees */
#define cosd(x) (cos(fmod((x),360) * M_PI / 180))
#define sind(x) (sin(fmod((x),360) * M_PI / 180))

#endif // FUNCTIONS_H
