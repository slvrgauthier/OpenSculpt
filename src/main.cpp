#include "gui/mainWindow.h"
#include <QApplication>

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include "GL/glut.h"
#else
    #include <GL/glut.h>
#endif

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
