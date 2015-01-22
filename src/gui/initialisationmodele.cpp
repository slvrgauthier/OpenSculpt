#include "gui/initialisationmodele.h"
#include "ui_initialisationmodele.h"

InitialisationModele::InitialisationModele(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialisationModele)
{
    ui->setupUi(this);
    modele = new QStandardItemModel;
    modele->setColumnCount(2);
    modele->setHorizontalHeaderLabels(QStringList() << "Modele" << "Description");
    ui->choixmodele->setModel(modele);
    ui->choixmodele->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /*Pour ajouter des modeles (stockés dans un fichier par exemple*/

    QList<QStandardItem*> listeElem;
    listeElem << new QStandardItem("Modele1") << new QStandardItem("Description Modele1");

    modele->appendRow(listeElem);
}

InitialisationModele::~InitialisationModele()
{
    delete ui;
}

void InitialisationModele::on_suivant_clicked()
{

    qDebug() << ui->choixmodele->currentIndex().row();
    type = CUBE;

        close();
}

void InitialisationModele::on_choixmodele_clicked(const QModelIndex &index)
{
    QMessageBox::information(this, "ok", "Tu as cliqué");
}
TYPE InitialisationModele::getType() const
{
    return type;
}
