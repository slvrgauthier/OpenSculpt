#include "model/MSphere.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

MSphere::MSphere() : m_radius(5.0)
{

}

void MSphere::initializeGL()
{

}
