#include "gui/glwidget.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

#include "tool/GTMove.h"
#include "tool/GTRotate.h"
#include "tool/GTScale.h"
#include "tool/LTInflate.h"
#include "tool/LTMove.h"
#include "tool/LTPinch.h"
#include "tool/LTSmooth.h"
#include "tool/LTAdd.h"

GLWidget::GLWidget(QWidget *parent ) : QGLWidget(parent)
{
    activeTool = NOTOOL;
    activeModel = NULL;
    mode_fill = false;

    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));

    m_timer.start(16);

    m_tools.push_back(new LTAdd());
    m_tools.push_back(new LTSmooth());
    m_tools.push_back(new LTMove());
    m_tools.push_back(new LTInflate());
    m_tools.push_back(new LTPinch());

    m_tools.push_back(new GTMove());
    m_tools.push_back(new GTRotate());
    m_tools.push_back(new GTScale());
}


void GLWidget::initializeGL()
{
    // View & rotation settings
    distance = -15.0;
    offsetX = 0;
    offsetY = 0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;

    // GL options
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

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
    gluLookAt(offsetX, -offsetY, -distance,
              offsetX, -offsetY, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot, 0.0f, 0.0f, 1.0f);

    int LightPos[4] = {(int)(distance/2),0,(int)(-distance/2),1};
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

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
    if (event->key() == Qt::Key_F) {
        mode_fill = !mode_fill;
    }
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
        rotateBy(dy, dx, 0);
    }

    if (event->buttons() & Qt::LeftButton)
    {
        if(activeTool == WTROTATE)
        {
            rotateBy(dy, dx, 0);
        }
        else if(activeTool == WTSCALE)
        {
            distance *= 1.0 + (1.0 * dy / 300.0);
            qDebug() << event->pos();
        }
        else if(activeTool == WTMOVE)
        {
            offsetX += (distance * dx / 600.0);
            offsetY += (distance * dy / 600.0);
        }
        else if(activeTool != NOTOOL && activeModel != NULL)
        {
            m_tools.at(activeTool)->action(activeModel, last_pos, event->pos(), distance, x_rot, y_rot, z_rot);
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

void GLWidget::selectModel(Model* model) {
    activeModel = model;
}

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

void GLWidget::resetView()
{
    distance = -15.0;
    offsetX = offsetY = x_rot = y_rot = z_rot = 0.0;
}
