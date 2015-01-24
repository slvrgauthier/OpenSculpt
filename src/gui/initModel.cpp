#include "gui/initModel.h"
#include "ui_initModel.h"

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

    QList<QStandardItem*> m_listElem;
    m_listElem << new QStandardItem("Modele1") << new QStandardItem("Description Modele1");

    m_model->appendRow(m_listElem);
}

InitModel::~InitModel()
{
    delete ui;
}

void InitModel::on_next_clicked()
{

    qDebug() << ui->choosemodel->currentIndex().row();
    m_type = CUBE;

        close();
}

void InitModel::on_choosemodel_clicked(const QModelIndex &index)
{
    QMessageBox::information(this, "ok", "Tu as cliqué");
}
TYPE InitModel::getType() const
{
    return m_type;
}
