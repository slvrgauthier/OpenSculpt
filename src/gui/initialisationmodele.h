#ifndef INITIALISATIONMODELE_H
#define INITIALISATIONMODELE_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>

#include "gui/parametragemodele.h"

namespace Ui {
class InitialisationModele;
}

class InitialisationModele : public QDialog
{
    Q_OBJECT

public:
    explicit InitialisationModele(QWidget *parent = 0);
    ~InitialisationModele();

    TYPE getType() const;

private slots:
    void on_next_clicked();

    void on_choosemodel_clicked(const QModelIndex &index);

private:
    Ui::InitialisationModele *ui;
    QStandardItemModel* m_model;

    TYPE m_type;
};

#endif // INITIALISATIONMODELE_H
