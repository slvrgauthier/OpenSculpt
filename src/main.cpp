#include "gui/fenprincipal.h"
#include <QApplication>
#include <GL/glut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    QApplication a(argc, argv);
    FenPrincipal w;
    w.show();

    return a.exec();
}
