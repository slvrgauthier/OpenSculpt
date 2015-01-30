#include "model/MSphere.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#endif
