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
<<<<<<< HEAD
    ModelManager m_manager;
    void addmodel();
=======
>>>>>>> 963f3ae54ae4ac9fe02d952f1fbd7ea571c8bc54

    void addmodel(Model *model);
    void removemodel();

private:
    void rotateBy(int x, int y, int z);

private:
    QTimer m_timer;
    ModelManager m_manager;
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
