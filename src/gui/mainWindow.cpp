#include "gui/mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include "gui/glwidget.h"
#include "model/ModelManager.h"
#include "model/func.h"
#include <QVector>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) //constructeur du programme principal
{
    ui->setupUi(this);
    this->hideDialog();
    ui->menuShow->setVisible(true);
    modelListLayout = new QVBoxLayout(ui->scrollArea);
    modelListLayout->setAlignment(Qt::AlignTop);
    modelList = new QWidget();
    modelList->setLayout(modelListLayout);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(modelList);
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
    ui->glwidget->clear();
    this->disableTool();
    this->hideDialog();
}

//Ouverture d'une boite de dialogue informant sur les concepteurs du programme
void MainWindow::on_actionA_propos_triggered()
{
   QMessageBox::information(this, "a propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER, LAMEIRA, PELADAN");
}

//Ecouteur sur le bouton select
void MainWindow::on_gtmove_clicked()
{
    this->disableTool();
    ui->gtmove->setChecked(true);
    ui->glwidget->enableTool(GTMOVE);
}

//Ecouteur sur le bouton rotation
void MainWindow::on_gtrotate_clicked()
{
    this->disableTool();
    ui->gtrotate->setChecked(true);
    ui->glwidget->enableTool(GTROTATE);
}

//Ecouteur sur le bouton redo
void MainWindow::on_redo_clicked()
{
    ui->redo->setChecked(false);
    // APPEL A LA FONCTION REDO
}

//Ecouteur sur le bouton zoom
void MainWindow::on_gtscale_clicked()
{
    this->disableTool();
    ui->gtscale->setChecked(true);
    ui->glwidget->enableTool(GTSCALE);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->glwidget->keyPressEvent(event);
}

//Creation d'un nouveau cube dans la scene
void MainWindow::on_initCube_clicked()
{
    this->disableTool();

    m_model = new MCube();
    ui->widgetDepth->setVisible(true);
    ui->widgetHeight->setVisible(true);
    ui->widgetWidth->setVisible(true);
    ui->widgetValidate->setVisible(true);
    ui->widgetSubdivide->setVisible(true); // Niveau de subdivision plutôt
    ui->widgetName->setVisible(true);
    ui->glwidget->addmodel(m_model);

    ui->spinBoxDepth->setValue(5.0);
    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxWidth->setValue(5.0);
    ui->sliderSubdivide->setValue(10); // Niveau de subdivision plutôt
    ui->textEditName->setText("NewCube");

    connect(ui->spinBoxDepth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxWidth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->sliderSubdivide, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));

}

//Creation d'une nouvelle sphere dans la scene
void MainWindow::on_initSphere_clicked()
{
    //ui->widgetradius->setVisible(true);
    ui->widgetValidate->setVisible(true);
}

//Ecouteur sur le bouton annuler
void MainWindow::on_pushCancel_clicked()
{
    this->hideDialog();
    ui->glwidget->removemodel();

}

//Ecouteur sur le bouton valider
void MainWindow::on_pushValid_clicked()
{
    this->hideDialog();

    disconnect(ui->spinBoxDepth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->spinBoxHeight, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->spinBoxWidth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    disconnect(ui->sliderSubdivide, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));
    m_model->setName(ui->textEditName->toPlainText());
    QPushButton *button = new QPushButton(m_model->getName());
    modelListLayout->addWidget(button); // Créer un widget spécifique
    qDebug()<<modelListLayout;

}

void MainWindow::updateLastModel() {
    m_model->setWidth(ui->spinBoxWidth->value());
    m_model->setHeight(ui->spinBoxHeight->value());
    m_model->setDepth(ui->spinBoxDepth->value());
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
    //ui->glwidget->clear(); RECODE : sous-menu avec cube, sphere...etc
}

void MainWindow::disableTool()
{
    ui->gtmove->setChecked(false);
    ui->gtrotate->setChecked(false);
    ui->redo->setChecked(false);
    ui->gtscale->setChecked(false);

    ui->glwidget->enableTool(NOTOOL);
}

void MainWindow::hideDialog()
{
    ui->widgetHeight->setVisible(false);
    ui->widgetWidth->setVisible(false);
    ui->widgetDepth->setVisible(false);
    ui->widgetValidate->setVisible(false);
    ui->widgetSubdivide->setVisible(false);
    ui->widgetName->setVisible(false);
}

void MainWindow::on_actionCr_er_un_Cube_triggered()
{
    m_model = new MCube();
    ui->widgetDepth->setVisible(true);
    ui->widgetHeight->setVisible(true);
    ui->widgetWidth->setVisible(true);
    ui->widgetValidate->setVisible(true);
    ui->widgetSubdivide->setVisible(true); // Niveau de subdivision plutôt
    ui->widgetName->setVisible(true);
    ui->glwidget->addmodel(m_model);

    ui->spinBoxDepth->setValue(5.0);
    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxWidth->setValue(5.0);
    ui->sliderSubdivide->setValue(10); // Niveau de subdivision plutôt
    ui->textEditName->setText("NewCube");

    connect(ui->spinBoxDepth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxWidth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->sliderSubdivide, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));
}

void MainWindow::on_rotate_clicked()
{
    this->disableTool();
    ui->rotate->setChecked(true);
    ui->glwidget->enableTool(GTROTATE);
}

void MainWindow::on_zoom_clicked()
{
    this->disableTool();
    ui->zoom->setChecked(true);
    ui->glwidget->enableTool(GTSCALE);
}
