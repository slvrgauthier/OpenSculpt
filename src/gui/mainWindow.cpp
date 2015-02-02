#include "gui/mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include "gui/glwidget.h"
#include "model/ModelManager.h"
#include "model/func.h"
#include <QVector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) //construteur du programme principal
{
    ui->setupUi(this);
    this->hideDialog();
    ui->menuShow->setVisible(true);
    layout = new QVBoxLayout;
    ui->hierarchy->setLayout(layout);


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
void MainWindow::on_actionNewProject_triggered()
{
    ui->widgetfenetre->clear();
    this->disableTool();
    this->hideDialog();
}

//Ouverture d'une boite de dialogue informant sur les concepteurs du programme
void MainWindow::on_actionA_propos_triggered()
{
   QMessageBox::information(this, "a propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER, LAMEIRA, PELADAN");
}

//Ecouteur sur le bouton select
void MainWindow::on_select_clicked()
{
    this->disableTool();
    ui->select->setChecked(true);
    ui->widgetfenetre->enableTool(GTMOVE);
}

//Ecouteur sur le bouton rotation
void MainWindow::on_rotation_clicked()
{
    this->disableTool();
    ui->rotation->setChecked(true);
    ui->widgetfenetre->enableTool(GTROTATE);
}

//Ecouteur sur le bouton redo
void MainWindow::on_redo_clicked()
{
    this->disableTool();
    ui->redo->setChecked(true);
    //ui->widgetfenetre->enableTool(REDO);
}

//Ecouteur sur le bouton zoom
void MainWindow::on_zoom_clicked()
{
    this->disableTool();
    ui->zoom->setChecked(true);
    ui->widgetfenetre->enableTool(WTSCALE);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->widgetfenetre->keyPressEvent(event);
}

//Creation d'un nouveau cube dans la scene
void MainWindow::on_initCube_clicked()
{
    this->disableTool();

    m_model = new MCube();
    ui->widgetheight->setVisible(true);
    ui->widgetwidth->setVisible(true);
    ui->widgetdepth->setVisible(true);
    ui->widgetvalid->setVisible(true);
    ui->widgetEdge->setVisible(true); // Niveau de subdivision plutôt
    ui->widgetName->setVisible(true);
    ui->widgetfenetre->addmodel(m_model);

    ui->doubleSpinBox->setValue(5.0);
    ui->doubleSpinBox_2->setValue(5.0);
    ui->doubleSpinBox_3->setValue(5.0);
    ui->horizontalSlider->setValue(10); // Niveau de subdivision plutôt
    ui->textEditName->setText("NewCube");

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));

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
    this->hideDialog();
    ui->widgetfenetre->removemodel();

}

//Ecouteur sur le bouton valider
void MainWindow::on_valid_clicked()
{
    this->hideDialog();

    disconnect(ui->doubleSpinBox, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->doubleSpinBox_2, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->doubleSpinBox_3, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->horizontalSlider, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));

    myLabel* m_name = new myLabel();
    m_name->setText(ui->textEditName->toPlainText());
    m_model->setName(ui->textEditName->toPlainText());
    m_hierarchy.push_back(m_name);
    qDebug()<<m_hierarchy;

    for(int i(0) ; i<m_hierarchy.size() ; i++)
    {

        layout->addWidget(m_hierarchy[i], 0, 0);

    }
    ui->hierarchy->show();
}

void MainWindow::updateLastModel() {
    m_model->setWidth(ui->doubleSpinBox->value());
    m_model->setHeight(ui->doubleSpinBox_2->value());
    m_model->setDepth(ui->doubleSpinBox_3->value());
    /* On fera une subdivision à la place ou une décimation
    m_model->verticesbyx(ui->horizontalSlider->value());
    m_model->verticesbyy(ui->horizontalSlider->value());
    m_model->verticesbyz(ui->horizontalSlider->value());
    */
}

//Permet de passer en mode plein ecran ou fenetrage
void MainWindow::on_actionFullscreen_triggered()
{

    if(!this->isFullScreen())
    {
        this->showFullScreen();
    }
    else
    {
        this->showNormal();
    }
}

void MainWindow::on_actionSave_as_triggered()
{

}

void MainWindow::on_actionNewObject_triggered()
{
    //ui->widgetfenetre->clear(); RECODE : sous-menu avec cube, sphere...etc
}

void MainWindow::disableTool()
{
    ui->select->setChecked(false);
    ui->rotation->setChecked(false);
    ui->redo->setChecked(false);
    ui->zoom->setChecked(false);

    ui->widgetfenetre->enableTool(NOTOOL);
}

void MainWindow::hideDialog()
{
    ui->widgetheight->setVisible(false);
    ui->widgetwidth->setVisible(false);
    ui->widgetdepth->setVisible(false);
    ui->widgetvalid->setVisible(false);
    ui->widgetEdge->setVisible(false);
    ui->widgetName->setVisible(false);
}
