#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H

#include <QDialog>

enum TYPE
{
    CUBE,
    CYLINDRE
};
namespace Ui {
class SettingModel;
}

class SettingModel : public QDialog
{
    Q_OBJECT

public:
    explicit SettingModel(TYPE type, QWidget *parent = 0);
    ~SettingModel();

private:
    Ui::SettingModel *ui;
};

#endif // SETTINGMODEL_H
