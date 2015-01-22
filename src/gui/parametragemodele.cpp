#include "gui/parametragemodele.h"
#include "ui_parametragemodele.h"

ParametrageModele::ParametrageModele(TYPE type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametrageModele)
{
    ui->setupUi(this);

    switch (type) {
    case CUBE:
        ui->widgetCylindre->setVisible(false);
        break;
    case CYLINDRE:
        ui->widgetCube->setVisible(false);
        break;
    default:
        break;
    }
}

ParametrageModele::~ParametrageModele()
{
    delete ui;
}
