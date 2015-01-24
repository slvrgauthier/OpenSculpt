#ifndef INITMODEL_H
#define INITMODEL_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>

#include "gui/settingModel.h"

namespace Ui {
class InitModel;
}

class InitModel : public QDialog
{
    Q_OBJECT

public:
    explicit InitModel(QWidget *parent = 0);
    ~InitModel();

    TYPE getType() const;

private slots:
    void on_next_clicked();

    void on_choosemodel_clicked(const QModelIndex &index);

private:
    Ui::InitModel *ui;
    QStandardItemModel* m_model;

    TYPE m_type;
};

#endif // INITMODEL_H
