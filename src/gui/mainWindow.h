#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "gui/initModel.h"
#include "gui/glwidget.h"

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
    void on_actionNew_triggered();
    void on_actionA_propos_triggered();
    void on_select_clicked();
    void on_rotation_clicked();
    void on_redo_clicked();
    void on_zoom_clicked();
    void on_showmesh_triggered();

    void on_actionCube_triggered();

    void on_pushButton_clicked();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    ModelManager m_manager;
};

#endif // MAINWINDOW_H
