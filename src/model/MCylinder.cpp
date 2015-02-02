#include "model/MCylinder.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

MCylinder::MCylinder() : m_radius(5.0), m_height(5.0)
{

}

void MCylinder::initializeGL()
{

}
