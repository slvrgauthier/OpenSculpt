#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QtGui/QMouseEvent>
#include "model/ModelManager.h"
#include "mainWindow.h"
#include "tool/Tool.h"

enum ETAT
{
    ZOOM,
    ROTATION,
    SELECT,
    REDO,
    VOIDi
};

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

    void setEtat(ETAT m_etat);

    void addmodel(Model *model);
    void removemodel();

private:
    void rotateBy(int x, int y, int z);

private:
    QTimer m_timer;
    ModelManager m_manager;
    QVector<Tool*> m_tools;
    int activeTool;
    ETAT etat;

    // View & rotation settings
    QPoint last_pos;
    float  distance;
    qreal  x_rot;
    qreal  y_rot;
    qreal  z_rot;

    // Render settings
    bool mode_fill;
};

#endif // GLWIDGET_H
