#include "gui/mainWindow.h"
#include "ui_mainWindow.h"

#include "gui/glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
}

void MainWindow::on_actionNew_triggered()
{
    InitModel m_new;
    m_new.exec();
}

void MainWindow::on_actionA_propos_triggered()
{
   QMessageBox::information(this, "a propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER, LAMEIRA, PELADAN");
}

void MainWindow::on_select_clicked()
{
    ui->select->setChecked(true);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(SELECT);
}

void MainWindow::on_rotation_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(true);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(ROTATION);
}

void MainWindow::on_redo_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(true);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(REDO);
}

void MainWindow::on_zoom_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(true);

    ui->widgetfenetre->setEtat(ZOOM);
}


void MainWindow::on_showmesh_triggered()
{

}

void MainWindow::on_actionCube_triggered()
{
    ui->widgetfenetre->addmodel();
}

void MainWindow::on_pushButton_clicked()
{
    ui->widgetfenetre->addmodel();
    qDebug()<<"la";
}
