#include "model/MTorus.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

MTorus::MTorus() : m_radius1(5.0), m_radius2(2.0)
{

}

void MTorus::initializeGL()
{

}
