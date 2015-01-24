#include "gui/settingModel.h"
#include "ui_settingModel.h"

SettingModel::SettingModel(TYPE type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingModel)
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

SettingModel::~SettingModel()
{
    delete ui;
}
