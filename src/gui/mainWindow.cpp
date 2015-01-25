#include "gui/mainWindow.h"
#include "ui_mainWindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->openGLWidget; //permet d'afficher la figure opengl
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

void MainWindow::on_select_pressed()
{

}


void MainWindow::on_rotation_pressed()
{

}

void MainWindow::on_zoom_pressed()
{

}


void MainWindow::on_select_clicked()
{
    if(ui->redo->isEnabled() && ui->rotation->isEnabled() && ui->zoom->isEnabled())
    {
        ui->redo->setEnabled(false);
        ui->rotation->setEnabled(false);
        ui->zoom->setEnabled(false);
        qDebug("llaaadff");

    }

    else if(!ui->redo->isEnabled() && !ui->rotation->isEnabled() && !ui->zoom->isEnabled())
    {
        qDebug("llaaa");
        ui->redo->setEnabled(true);
        ui->rotation->setEnabled(true);
        ui->zoom->setEnabled(true);
    }

}

void MainWindow::on_rotation_clicked()
{
    if(ui->redo->isEnabled() && ui->select->isEnabled() && ui->zoom->isEnabled())
    {
        ui->redo->setEnabled(false);
        ui->select->setEnabled(false);
        ui->zoom->setEnabled(false);
        qDebug("llaaadff");

    }

    else if(!ui->redo->isEnabled() && !ui->select->isEnabled() && !ui->zoom->isEnabled())
    {
        qDebug("llaaa");
        ui->redo->setEnabled(true);
        ui->select->setEnabled(true);
        ui->zoom->setEnabled(true);
    }
}

void MainWindow::on_redo_clicked()
{
    if(ui->select->isEnabled() && ui->rotation->isEnabled() && ui->zoom->isEnabled())
    {
        ui->select->setEnabled(false);
        ui->rotation->setEnabled(false);
        ui->zoom->setEnabled(false);
        qDebug("llaaadff");

    }

    else if(!ui->select->isEnabled() && !ui->rotation->isEnabled() && !ui->zoom->isEnabled())
    {
        qDebug("llaaa");
        ui->select->setEnabled(true);
        ui->rotation->setEnabled(true);
        ui->zoom->setEnabled(true);
    }
}

void MainWindow::on_zoom_clicked()
{
    if(ui->redo->isEnabled() && ui->rotation->isEnabled() && ui->select->isEnabled())
    {
        ui->redo->setEnabled(false);
        ui->rotation->setEnabled(false);
        ui->select->setEnabled(false);
        qDebug("llaaadff");

    }

    else if(!ui->redo->isEnabled() && !ui->rotation->isEnabled() && !ui->select->isEnabled())
    {
        qDebug("llaaa");
        ui->redo->setEnabled(true);
        ui->rotation->setEnabled(true);
        ui->select->setEnabled(true);
    }
}
