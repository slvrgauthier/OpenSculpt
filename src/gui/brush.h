#ifndef BRUSH_H
#define BRUSH_H

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #include <windows.h>
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <QPoint>
#include "mesh/functions.h"

class Brush {

    // ================== PUBLIC CONSTRUCTORS ==================
public:
    Brush();
    ~Brush();
    // =========================================================


    // ================== PUBLIC MEMBERS ==================
public:
    void paintGL(QPoint mouse);
    // ====================================================


    // ================== PUBLIC ACCESSORS ==================
public:
    float getSize() const;
    void setSize(float size);

    float getStrength() const;
    void setStrength(float strength);
    // ======================================================


    // ================== PROPERTIES ==================
private:
    float m_size;
    float m_strength;
};

#endif // BRUSH_H
