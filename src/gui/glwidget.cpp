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
#include "mesh/functions.h"

GLWidget::GLWidget(QWidget *parent ) : QGLWidget(parent)
{
    activeTool = NOTOOL;
    activeMesh = -1;
    mode_fill = false;
    brushSize = 3;

    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateActiveMesh()));

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

    // Brush
/*    glColor3d(1,0,0);
    glBegin(GL_LINE_LOOP);
        for (int i=0; i < 360; ++i) {
            glVertex3f(last_pos.x() + cosd(i)*brushSize, last_pos.y() + sind(i)*brushSize, 0);
        }
    glEnd();*/

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
        }
        else if(activeTool == WTMOVE)
        {
            offsetX += (distance * dx / 600.0);
            offsetY += (distance * dy / 600.0);
        }
        else if(activeTool != NOTOOL && m_manager.getMesh(activeMesh) != NULL)
        {
            m_tools.at(activeTool)->action(m_manager.getMesh(activeMesh), last_pos, event->pos(), brushSize, distance, x_rot, y_rot, z_rot);
        }
        else
        {
            qDebug() << "NOTOOL or Mesh NULL";
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

void GLWidget::enableTool(TOOL tool) { activeTool = tool; }
void GLWidget::selectMesh(Mesh *mesh) {
    if(mesh == NULL) {
        activeMesh = -1;
    }
    else {
        for(int i=0 ; i < m_manager.getSize() ; ++i) {
            if(m_manager.getMesh(i) == mesh) {
                activeMesh = i;
            }
        }
    }
}

void GLWidget::updateActiveMesh() {
    if(activeMesh >= 0) {
        m_manager.updateMesh(activeMesh);
    }
    else {
        m_manager.updateLastMesh();
    }
}

void GLWidget::addMesh(Mesh *mesh) { m_manager.addMesh(mesh); }
void GLWidget::removeMesh(Mesh *mesh) {  m_manager.removeMesh(mesh); }
void GLWidget::clear() { m_manager.clear(); }

void GLWidget::resetView()
{
    distance = -15.0;
    offsetX = offsetY = x_rot = y_rot = z_rot = 0.0;
}

void GLWidget::undo()
{

}

void GLWidget::redo()
{

}
