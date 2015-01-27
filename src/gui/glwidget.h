#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QtGui/QMouseEvent>
#include "model/ModelManager.h"
#include "mainWindow.h"

enum ETAT
{
    ZOOM,
    ROTATION,
    SELECT,
    REDO,
    VOID
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
    ModelManager m_manager;


private:
    void rotateBy(int x, int y, int z);

private:
    QTimer m_timer;


    // View & rotation settings
    QPoint last_pos;
    float  distance;
    qreal  x_rot;
    qreal  y_rot;
    qreal  z_rot;

    // Render settings
    bool mode_fill;

    ETAT etat;

};

#endif // GLWIDGET_H
