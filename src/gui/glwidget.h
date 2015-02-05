#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QtGui/QMouseEvent>
#include "model/ModelManager.h"
#include "mainWindow.h"
#include "tool/Tool.h"

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
    void selectModel(Model* model);

    void addmodel(Model *model);
    void removemodel();
    void clear();

    void resetView();
    void undoview();


private:
    void rotateBy(int x, int y, int z);

private:
    QTimer m_timer;
    ModelManager m_manager;
    QVector<Tool*> m_tools;
    TOOL activeTool;
    Model* activeModel;

    // View & rotation settings
    QPoint last_pos;
    float distancesave;
    float distance;
    float offsetXsave;
    float offsetYsave;
    qreal x_rotsave;
    qreal y_rotsave;
    qreal z_rotsave;
    float offsetX;
    float offsetY;
    qreal x_rot;
    qreal y_rot;
    qreal z_rot;

    // Render settings
    bool mode_fill;

};

#endif // GLWIDGET_H
