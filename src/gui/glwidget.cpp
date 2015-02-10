#include "gui/glwidget.h"

#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WIN32__)
    #define GLUT_DISABLE_ATEXIT_HACK
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    activeTool = NOTOOL;
    activeMesh = -1;
    mode_fill = true;
    m_brush.setSize(.5);
    auto_sub = false;

    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateGL()));
    connect(&m_timer, SIGNAL(timeout()),this, SLOT(updateActiveMesh()));

    m_timer.start(16);
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

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(offsetX, -offsetY, -distance,
              offsetX, -offsetY, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot, 0.0f, 0.0f, 1.0f);

    int LightPos[4] = {(int)(offsetX - distance),(int)-offsetY,(int)(-distance/2),1};
    glLightiv(GL_LIGHT0,GL_POSITION,LightPos);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // Brush
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //qglColor(QColor(255, 0, 0, 128));
    //m_brush.paintGL(QVector3D(last_pos.x()-this->width()/2.,this->height()/2.-last_pos.y(),0) * (-distance/900.));

    // Draw meshes
    if(mode_fill) {
        //qglColor(Qt::lightGray);
        m_manager.paintGL();
    }

    //qglColor(Qt::black);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_manager.paintGL();
}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {

    case Qt::Key_F:
        if(!event->modifiers()) { mode_fill = true; }
        break;

    case Qt::Key_W:
        if(!event->modifiers()) { mode_fill = false; }
        break;

    default:
        break;
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
            if(auto_sub) {
                m_tool.subdivideAuto(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), 1.);
            }

            switch(activeTool) {

            // GLOBAL TOOLS
            case GTMOVE:
                m_tool.gtmove(m_manager.getMesh(activeMesh), rotateXYZ(QVector3D(-dx, dy, 0), QVector3D(x_rot, y_rot, z_rot)) * (distance / 900.0));
                break;

            case GTROTATE:
                m_tool.gtrotate(m_manager.getMesh(activeMesh), QVector3D(dy, dx, 0));
                break;

            case GTSCALE:
                m_tool.gtscale(m_manager.getMesh(activeMesh), QVector3D(0, dy, 0));
                break;

            // LOCAL TOOLS
            case LTADD:
                m_tool.ltadd(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), event->modifiers());
                break;

            case LTINFLATE:
                m_tool.ltinflate(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), event->modifiers());
                break;

            case LTMOVE:
                m_tool.ltmove(m_manager.getMesh(activeMesh), last_pos, rotateXYZ(QVector3D(-dx, dy, 0), QVector3D(x_rot, y_rot, z_rot)) * (distance / 900.0), m_brush.getSize());
                break;

            case LTPINCH:
                m_tool.ltpinch(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), event->modifiers());
                break;

            case LTSMOOTH:
                m_tool.ltsmooth(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize());
                break;

            default:
                qDebug() << "The tool isn't defined";
                break;
            }
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
    activeMesh = -1;
    for(int i=0 ; i < m_manager.getSize() ; ++i) {
        if(m_manager.getMesh(i) == mesh) {
            activeMesh = i;
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
