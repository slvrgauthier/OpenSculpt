#include "model/MCone.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

MCone::MCone() : m_radius1(5.0), m_radius2(0.1), m_height(5.0)
{

}

void MCone::initializeGL()
{

}
