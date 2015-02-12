#include "gui/mainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QSplashScreen>
#include <QBitmap>

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #include <windows.h>
    #define GLUT_DISABLE_ATEXIT_HACK
    #include "GL/glut.h"

#else
    #include <GL/glut.h>
#endif

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    QPixmap logo("../src/data/icons/OpenSculpt.png");
    QSplashScreen splash(logo);
    splash.setWindowFlags(Qt::WindowStaysOnTopHint);
    splash.setMask(logo.mask());

    splash.show();
    MainWindow window;
    splash.finish(&window);
    window.show();

    return app.exec();
}
