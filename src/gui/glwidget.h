#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QGLWidget>
#include <QTimer>
#include "model/Model.h"

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

private:
    QTimer m_timer;
    Model m_model;
};

#endif // GLWIDGET_H
