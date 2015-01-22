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
    void on_suivant_clicked();

    void on_choixmodele_clicked(const QModelIndex &index);

private:
    Ui::InitialisationModele *ui;
    QStandardItemModel* modele;

    TYPE type;
};

#endif // INITIALISATIONMODELE_H
