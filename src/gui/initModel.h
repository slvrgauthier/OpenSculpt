#ifndef INITMODEL_H
#define INITMODEL_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>



namespace Ui {
class InitModel;
}

class InitModel : public QDialog
{
    Q_OBJECT

public:
    explicit InitModel(QWidget *parent = 0);
    ~InitModel();



private slots:
    //void on_next_clicked();

    void on_choosemodel_clicked(const QModelIndex &index);

private:
    Ui::InitModel *ui;
    QStandardItemModel* m_model;


};

#endif // INITMODEL_H
