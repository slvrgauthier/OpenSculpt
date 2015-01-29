#include "gui/mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include "gui/glwidget.h"
#include "model/ModelManager.h"
#include "model/func.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) //construteur du programme principal
{
    ui->setupUi(this);
    ui->widgetheight->setVisible(false);
    ui->widgetwidth->setVisible(false);
    ui->widgetdepth->setVisible(false);
    ui->widgetvalid->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Ouverture des scenes crées precedement
void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
}

//Creation d'une nouvelle fenetre avec tous les parametres reinitialises
void MainWindow::on_actionNew_triggered()
{

    MainWindow *newWindow= new MainWindow();
    QMessageBox::StandardButton initialise;
    initialise = QMessageBox::question(this, "initialiser", "Voulez-vous écraser cette fenetre?",QMessageBox::Yes|QMessageBox::No);

    if (initialise == QMessageBox::Yes)
    {
        this->close();
        newWindow->show();
     }
}

//Ouverture d'une boite de dialogue informant sur les concepteurs du programme
void MainWindow::on_actionA_propos_triggered()
{
   QMessageBox::information(this, "a propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER, LAMEIRA, PELADAN");
}

//Ecouteur sur le bouton select
void MainWindow::on_select_clicked()
{
    ui->select->setChecked(true);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(SELECT);
}

//Ecouteur sur le bouton ratation
void MainWindow::on_rotation_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(true);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(ROTATION);
}

//Ecouteur sur le bouton redo
void MainWindow::on_redo_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(true);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->setEtat(REDO);
}

//Ecouteur sur le bouton zoom
void MainWindow::on_zoom_clicked()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(true);

    ui->widgetfenetre->setEtat(ZOOM);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->widgetfenetre->keyPressEvent(event);
}

//Creation d'un nouveau cube dans la scene
void MainWindow::on_initCube_clicked()
{
    m_model = createModel<MCube>();
    ui->widgetheight->setVisible(true);
    ui->widgetwidth->setVisible(true);
    ui->widgetdepth->setVisible(true);
    ui->widgetvalid->setVisible(true);
    ui->widgetfenetre->addmodel(m_model);

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel())); //apparemment impossible sans QObject... -> à contourner
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
}

//Creation d'une nouvelle sphere dans la scene
void MainWindow::on_initSphere_clicked()
{
    //ui->widgetradius->setVisible(true);
    ui->widgetvalid->setVisible(true);
}

//Ecouteur sur le bouton annuler
void MainWindow::on_cancel_clicked()
{
    ui->widgetheight->setVisible(false);
    ui->widgetwidth->setVisible(false);
    ui->widgetdepth->setVisible(false);
    ui->widgetvalid->setVisible(false);
    ui->widgetfenetre->removemodel();

}

//Ecouteur sur le bouton valider
void MainWindow::on_valid_clicked()
{
    ui->widgetheight->setVisible(false);
    ui->widgetwidth->setVisible(false);
    ui->widgetdepth->setVisible(false);
    ui->widgetvalid->setVisible(false);

    disconnect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
}

void MainWindow::updateLastModel() { //TEST
    m_model->setWidth(ui->doubleSpinBox->value());
    m_model->setHeight(ui->doubleSpinBox_2->value());
    m_model->setDepth(ui->doubleSpinBox_3->value());
}
