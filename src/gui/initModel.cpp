#include "gui/initModel.h"
#include "ui_initModel.h"
#if defined(__APPLE__) && (__MACH__)
    #include <GLUT/glut.h>
#elif defined(__WINDOWS__)
    #include <GL/glut.h>
#else
    #include <GL/glut.h>
#endif

InitModel::InitModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitModel)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel;
    m_model->setColumnCount(2);
    m_model->setHorizontalHeaderLabels(QStringList() << "Modele" << "Description");
    ui->choosemodel->setModel(m_model);
    ui->choosemodel->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /*Pour ajouter des modeles (stockés dans un fichier par exemple*/

    QList<QStandardItem*> m_Cube;
    m_Cube << new QStandardItem("Cube") << new QStandardItem("Cube en 3D");
    m_model->appendRow(m_Cube);
    QList<QStandardItem*> m_Cylindre;
    m_Cylindre << new QStandardItem("Cylindre") << new QStandardItem("Cylindre en 3D");
    m_model->appendRow(m_Cylindre);
}

InitModel::~InitModel()
{
    delete ui;
}


void InitModel::on_choosemodel_clicked(const QModelIndex &index)
{


    if(ui->choosemodel->currentIndex().row()==0)
    {
        QMessageBox::information(this, "Cube", "Tu as cliqué sur le Cube");

        ui->widgetCube->setEnabled(true);
        ui->widgetCylindre->setEnabled(false);


    }
    if(ui->choosemodel->currentIndex().row()==1)
    {
        QMessageBox::information(this, "Cylindre", "Tu as cliqué sur le Cylindre");

        ui->widgetCylindre->setEnabled(true);
        ui->widgetCube->setEnabled(false);
        glutWireTeapot(0.6);
    }



}

