#include "gui/fenprincipal.h"
#include "ui_fenprincipal.h"

FenPrincipal::FenPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenPrincipal)
{
    ui->setupUi(this);

    //ui->openGLWidget; //permet d'afficher la figure opengl
}

FenPrincipal::~FenPrincipal()
{
    delete ui;
}

void FenPrincipal::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
}


void FenPrincipal::on_actionNew_triggered()
{
    InitialisationModele m_new;
    m_new.exec();

    TYPE type = m_new.getType();

    ParametrageModele param(type);
    param.exec();

}
