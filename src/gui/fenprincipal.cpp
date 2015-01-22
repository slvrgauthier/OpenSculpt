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

void FenPrincipal::on_actionOuvrir_triggered()
{
    QFileDialog::getOpenFileName(this,"choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
}


void FenPrincipal::on_actionNouveau_triggered()
{
    InitialisationModele nouveau;
    nouveau.exec();

    TYPE type = nouveau.getType();

    ParametrageModele param(type);
    param.exec();

}
