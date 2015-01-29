/*
 * func.h
 * @author : Team OpenSculpt
 *
 * This file gives some useful functions outside any class.
 *
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QVector>
#include <stdlib.h>
#include <cmath>

using namespace std;

/* contains is a basic search function of an element in a QVector
 * In : v a QVector of T object references, ptr a T object reference
 * Out : a boolean, true if ptr is in v, false if not.
 */
template<typename T>
bool contains(QVector<T*> v, T* ptr) {
    for(unsigned int i = 0 ; i < v.size() ; ++i) {
        if(v[i] == ptr) {
            return true;
        }
    }
    return false;
}

/* createModel is usable to create a new model of class T */
template<typename T>
T* createModel() {
    return new T();
}

/* cosinus and sinus with degrees */
#define cosd(x) (cos(fmod((x),360) * M_PI / 180))
#define sind(x) (sin(fmod((x),360) * M_PI / 180))

#endif // FUNCTIONS_H
