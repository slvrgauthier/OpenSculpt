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

#include "tool/GTMove.h"
#include "tool/GTRotate.h"
#include "tool/GTScale.h"
#include "tool/LTInflate.h"
#include "tool/LTMove.h"
#include "tool/LTPinch.h"
#include "tool/LTSmooth.h"
#include "model/func.h"

GLWidget::GLWidget(QWidget *parent ) : QGLWidget(parent)
{
    activeTool = NOTOOL;
    mode_fill = false;

    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));

    m_timer.start(16);

    m_tools.push_back(new GTMove());
    m_tools.push_back(new GTRotate());
    m_tools.push_back(new GTScale());
    m_tools.push_back(new LTInflate());
    m_tools.push_back(new LTMove());
    m_tools.push_back(new LTPinch());
    m_tools.push_back(new LTSmooth());
}


void GLWidget::initializeGL()
{
    // View & rotation settings
    distance = -15.0;
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

    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);


    // Draw map
    qglColor(Qt::lightGray);
    //glColor3d(1,0,0); // face rouge

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
    float coef = distance / 900.0; // Compensation perspective

    float x,y,z, x_,y_,z_;
    //Rotation autour de X
    x_ = -dx, y_ = dy*cosd(x_rot), z_ = dy*sind(x_rot);
    //Rotation autour de Y
    x = x_*cosd(y_rot)+z_*sind(y_rot), y = y_, z = z_*cosd(y_rot)-x_*sind(y_rot);
    //Rotation autour de Z
    x_ = x*cosd(z_rot)-y*sind(z_rot), y_ = x*sind(z_rot)+y*cosd(z_rot), z_ = z;
    // Mise à l'échelle
    x = x_*coef, y = y_*coef, z = -z_*coef;

    QVector3D move(x,y,z); // Mouvement dans le repère scène

    if (event->buttons() & Qt::RightButton)
    {
        qDebug() << "WTROTATE droite";
        rotateBy(dy, 0, 0);
        rotateBy(0, dx, 0);
    }

    if (event->buttons() & Qt::LeftButton)
    {
        if(activeTool == WTROTATE)
        {
            qDebug() << "WTROTATE gauche";
            rotateBy(dy, 0, 0);
            rotateBy(0, dx, 0);
        }
        else if(activeTool == WTSCALE)
        {
            qDebug() << "WTSCALE";
            distance *= 1.0 + (1.0 * dy / 300.0);
            qDebug() << event->pos();
        }/*
        else if(activeTool == REDO)
        {
            qDebug() << "REDO";
        }*/
        else if(activeTool != NOTOOL)
        {
            Model* model = m_manager.getModel("NewCube"); //RECODE : indice pris dans la hiérarchie d'objet
            m_tools.at(activeTool)->action(model, m_manager.getGLpos(event->pos()), move);
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

//Modifie l'outil associe a la souris
void GLWidget::enableTool(TOOL tool)
{
    activeTool = tool;
}

//Ajout d'un nouveau modele de différent type
void GLWidget::addmodel(Model *model) {
    m_manager.addModel(model);
}

void GLWidget::removemodel()
{
    m_manager.removeModel();
}

void GLWidget::clear()
{
    m_manager.clear();
}
