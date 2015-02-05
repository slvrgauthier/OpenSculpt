#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "gui/glwidget.h"
#include <QString>
#include <QLabel>
#include<QGridLayout>

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

    // Up toolBar
    void on_wtmove_clicked();
    void on_wtrotate_clicked();
    void on_wtscale_clicked();

    void on_redo_clicked();

    void on_initCube_clicked();
    void on_initSphere_clicked();

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
    void on_pushCancel_clicked();
    void on_pushValid_clicked();
    void show_param();

private slots:
    void keyPressEvent(QKeyEvent *event);
    void updateLastModel();
    void updatesubdivide();
    void disableTool();
    void hideDialog();

    void on_pushRemplace_clicked();

    void on_subdivide_clicked();

    void on_undo_clicked();

private:
    Ui::MainWindow *ui;
    Model *m_model;
    QMap<QPushButton*, Model*> m_modelList;
    QPushButton* button;
    QVector<QPushButton *> listObject;
};

#endif // MAINWINDOW_H
