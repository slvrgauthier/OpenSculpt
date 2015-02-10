#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QtGui/QMouseEvent>
#include "brush.h"
#include "mesh/MeshManager.h"
#include "mesh/MeshTool.h"
#include "mesh/MeshProcessing.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void enableTool(TOOL tool);
    void selectMesh(Mesh *mesh);

    void addMesh(Mesh *mesh);
    void removeMesh(Mesh *mesh);
    void clear();

    void resetView();
    void undo();
    void redo();

public slots:
    void setBrushSize(double size);
    void setBrushStrength(double strength);
    void setAutoSub(int state);

private slots:
    void updateActiveMesh();

private:
    void rotateBy(int x, int y, int z);

private:
    QTimer m_timer;
    MeshManager m_manager;
    MeshTool m_tool;
    MeshProcessing m_processing;
    TOOL activeTool;
    int activeMesh;
    Brush m_brush;

    // View & rotation settings
    QPoint last_pos;
    float distance;
    float offsetX;
    float offsetY;
    qreal x_rot;
    qreal y_rot;
    qreal z_rot;

    // Render settings
    bool mode_fill;
    bool auto_sub;

};

#endif // GLWIDGET_H
