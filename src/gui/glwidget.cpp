#include "gui/glwidget.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

GLWidget::GLWidget(QWidget *parent ) : QGLWidget(parent)
{
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));
    m_timer.start(16);
}


void GLWidget::initializeGL()
{
    /*glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/
    m_model.initializeGL();
}
void GLWidget::paintGL()
{
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(0.5, 1, 1, 1);
    glColor3f(1, 0.6, 0);
    glutSolidTeapot(0.6);*/
    m_model.paintGL();
}
void GLWidget::resizeGL(int w, int h)
{
    /*glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);*/
    m_model.resizeGL(w,h);
}

void GLWidget::keyPressEvent(QKeyEvent *event) { m_model.keyPressEvent(event); }
void GLWidget::mousePressEvent(QMouseEvent *event) { m_model.mousePressEvent(event); }
void GLWidget::mouseMoveEvent(QMouseEvent *event) { m_model.mouseMoveEvent(event); }
void GLWidget::wheelEvent(QWheelEvent *event) { m_model.wheelEvent(event); }
