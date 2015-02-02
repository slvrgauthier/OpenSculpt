#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "gui/glwidget.h"
#include <QString>
#include <QLabel>
#include<QGridLayout>
#include"gui/mylabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionNewProject_triggered();
    void on_actionA_propos_triggered();
    void on_select_clicked();
    void on_rotation_clicked();
    void on_redo_clicked();
    void on_zoom_clicked();
    void keyPressEvent(QKeyEvent *event);
    void on_initCube_clicked();
    void on_initSphere_clicked();
    void on_cancel_clicked();
    void on_valid_clicked();
    void updateLastModel();
    void disableTool();
    void hideDialog();


    //void on_pushButton_clicked();

    void on_actionFullscreen_triggered();

    void on_actionSave_as_triggered();

    void on_actionNewObject_triggered();


private:
    Ui::MainWindow *ui;
    Model* m_model;
    QVector<myLabel*> m_hierarchy;
    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
