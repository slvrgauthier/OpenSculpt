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
    mode_fill = 3;
    m_brush.setSize(1.5); // between 0 and 10
    m_brush.setStrength(.05); // between 0 and 0.10
    auto_sub = false;
    auto_dec = true;

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
    qglClearColor(Qt::white);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);

    // Light position
    glEnable(GL_LIGHT0);
    int Light0Pos[4] = {(int)(offsetX - distance),(int)-offsetY,(int)(-distance/2),1};
    glLightiv(GL_LIGHT0,GL_POSITION,Light0Pos);

    // Wireframe offset
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1,-1);
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

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // Draw meshes
    if(mode_fill & 2) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        m_manager.paintGL(activeMesh);
    }

    if(mode_fill & 1) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_manager.paintGL((mode_fill)? -2 : -1);
    }

    // Brush
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_brush.paintGL(mapFromGlobal(this->cursor().pos()), m_manager.getMesh(activeMesh));
}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {

    case Qt::Key_F:
        if(!event->modifiers()) { mode_fill = (mode_fill == 3)? 2 : 3; }
        if(event->modifiers()&Qt::ControlModifier) { switchFillModes(); }
        break;

    case Qt::Key_W:
        if(!event->modifiers()) { mode_fill = (mode_fill == 3)? 1 : 3;; }
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
            if(auto_sub) { m_tool.subdivideAuto(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize()); }
            //if(auto_dec) { m_tool.decimateAuto(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize()); }

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
                m_tool.ltadd(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), m_brush.getStrength(), event->modifiers());
                break;

            case LTINFLATE:
                m_tool.ltinflate(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), m_brush.getStrength(), event->modifiers());
                break;

            case LTMOVE:
                m_tool.ltmove(m_manager.getMesh(activeMesh), last_pos, rotateXYZ(QVector3D(-dx, dy, 0), QVector3D(x_rot, y_rot, z_rot)) * (distance / 900.0), m_brush.getSize());
                break;

            case LTPINCH:
                m_tool.ltpinch(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), m_brush.getStrength(), event->modifiers());
                break;

            case LTSMOOTH:
                m_tool.ltsmooth(m_manager.getMesh(activeMesh), last_pos, m_brush.getSize(), m_brush.getStrength(), event->modifiers());
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

void GLWidget::enableTool(TOOL tool) { activeTool = tool; }

void GLWidget::selectMesh(Mesh *mesh) {
    activeMesh = -1;
    for(int i=0 ; i < m_manager.getSize() ; ++i) {
        if(m_manager.getMesh(i) == mesh) {
            activeMesh = i;
        }
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

void GLWidget::setBrushSize(double size) {
    m_brush.setSize((float)size);
}

void GLWidget::setBrushStrength(double strength) {
    m_brush.setStrength((float)strength / 1000);
}

void GLWidget::setAutoSub(int state) { auto_sub = (state == Qt::Checked); }

void GLWidget::updateActiveMesh() {
    if(activeMesh >= 0) {
        m_manager.updateMesh(activeMesh);
    }
    else {
        m_manager.updateLastMesh();
    }
}

void GLWidget::switchFillModes() {
    mode_fill = (mode_fill == 1)? 3 : 1;
}

void GLWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}
