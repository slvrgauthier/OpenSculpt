#include "gui/glwidget.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#endif

GLWidget::GLWidget(QWidget *parent ) : QGLWidget(parent)
{
    etat = VOIDi;
    mode_fill = false;

<<<<<<< HEAD
    m_manager.addModel(new MCube());

=======
>>>>>>> 963f3ae54ae4ac9fe02d952f1fbd7ea571c8bc54
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));

    m_timer.start(16);
}


void GLWidget::initializeGL()
{
    // View & rotation settings
    distance = -12.0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;

    // GL options
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);/*
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);*/

    // ModelManager init
    m_manager.initializeGL();
}
void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, mode_fill ? GL_FILL : GL_LINE);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -distance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot / 16.0f, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);


    // Draw map
    qglColor(Qt::lightGray);

    m_manager.paintGL();
}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F)
        mode_fill = !mode_fill;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_pos.x();
    int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::RightButton)
    {
        qDebug() << "ROTATION droite";
        rotateBy(dy*8, 0, 0);
        rotateBy(0, dx*8, 0);
    }

    if (event->buttons() & Qt::LeftButton)
    {
        if(etat == ROTATION)
        {
            qDebug() << "ROTATION gauche";
            rotateBy(dy*8, 0, 0);
            rotateBy(0, dx*8, 0);
        }
        else if(etat == ZOOM)
        {
            qDebug() << "ZOOM";
            distance *= 1.0 + (1.0 * dy / 300.0);
            qDebug() << event->pos();
        }
        else if(etat == REDO)
        {
            qDebug() << "REDO";
        }
        else if(etat == SELECT)
        {
            QVector3D p = m_manager.getGLpos(event->pos());
            if(p.isNull()) {
                qDebug() << "SELECT : NULL";
            }
            else {
                qDebug() << "SELECT : " << p;
            }
        }
        else
        {
            qDebug() << "VOID";
        }
    }

    last_pos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 - (1.0 * event->delta() / 1200.0);
}

void GLWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}

//Modifie l'etat associee a la souris
void GLWidget::setEtat(ETAT m_etat)
{
    etat = m_etat;
}

<<<<<<< HEAD
void GLWidget::addmodel() { m_manager.addModel(new MCube());}
=======
//Ajout d'un nouveau modele de différent type
void GLWidget::addmodel(Model *model) {
    m_manager.addModel(model);
}

void GLWidget::removemodel()
{
    m_manager.removeModel();
}
>>>>>>> 963f3ae54ae4ac9fe02d952f1fbd7ea571c8bc54
