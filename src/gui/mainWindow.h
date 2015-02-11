#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QGridLayout>
#include "mesh/MeshProcessing.h"

#include "modelbutton.h"

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
    // Left panel
    void on_ltadd_clicked();
    void on_ltsmooth_clicked();
    void on_ltmove_clicked();
    void on_ltinflate_clicked();
    void on_ltpinch_clicked();

    void on_gtmove_clicked();
    void on_gtrotate_clicked();
    void on_gtscale_clicked();

    void on_debug_clicked();

    // Up toolBar
    void on_select_clicked();

    void on_wtmove_clicked();
    void on_wtrotate_clicked();
    void on_wtscale_clicked();

    void on_undo_clicked();
    void on_redo_clicked();
    void on_subdivide_clicked();
    void on_decimate_clicked();

    void on_init();
    void on_initCube_clicked();
    void on_initSphere_clicked();
    void on_initCylinder_clicked();
    void on_initCone_clicked();
    void on_initTorus_clicked();

    // MenuFile
    void on_actionNewProject_triggered();
    void on_actionNewCube_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_as_triggered();

    // MenuView
    void on_actionFullscreen_triggered();

    // MenuHelp
    void on_actionAbout_triggered();

    // Right panel
    void on_pushRemplace_clicked();
    void on_pushCancel_clicked();
    void on_pushValid_clicked();
    void on_pushDelete_clicked();
    void on_pushDuplicate_clicked();

private slots:
    // Update the last model
    void updateCube();
    void updateSphere();
    void updateCylinder();
    void updateCone();
    void updateTorus();

private slots:
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void disableTool();
    void hideDialog();
    void showDialog();
    void selectModel();

private:
    Ui::MainWindow *ui;
    Mesh *m_mesh;
    QMap<QPushButton*, Mesh*> m_meshList;
    MeshProcessing m_processing;
};

#endif // MAINWINDOW_H
