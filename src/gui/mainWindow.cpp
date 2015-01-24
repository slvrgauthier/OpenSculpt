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

    TYPE type = m_new.getType();

    SettingModel param(type);
    param.exec();

}
