#include "gui/mainWindow.h"
#include <QApplication>

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #include <GL/glut.h>
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
