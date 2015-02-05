#include "gui/mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include "gui/glwidget.h"
#include "model/ModelManager.h"
#include "model/func.h"
#include <QVector>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->hideDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ===================================================
// LEFT PANEL

void MainWindow::on_ltadd_clicked()
{
    this->disableTool();
    ui->ltadd->setChecked(true);
    ui->glwidget->enableTool(LTADD);
}

void MainWindow::on_ltsmooth_clicked()
{
    this->disableTool();
    ui->ltsmooth->setChecked(true);
    ui->glwidget->enableTool(LTSMOOTH);
}

void MainWindow::on_ltmove_clicked()
{
    this->disableTool();
    ui->ltmove->setChecked(true);
    ui->glwidget->enableTool(LTMOVE);
}

void MainWindow::on_ltinflate_clicked()
{
    this->disableTool();
    ui->ltinflate->setChecked(true);
    ui->glwidget->enableTool(LTINFLATE);
}

void MainWindow::on_ltpinch_clicked()
{
    this->disableTool();
    ui->ltpinch->setChecked(true);
    ui->glwidget->enableTool(LTPINCH);
}

void MainWindow::on_gtmove_clicked()
{
    this->disableTool();
    ui->gtmove->setChecked(true);
    ui->glwidget->enableTool(GTMOVE);
}

void MainWindow::on_gtrotate_clicked()
{
    this->disableTool();
    ui->gtrotate->setChecked(true);
    ui->glwidget->enableTool(GTROTATE);
}

void MainWindow::on_gtscale_clicked()
{
    this->disableTool();
    ui->gtscale->setChecked(true);
    ui->glwidget->enableTool(GTSCALE);
}

// ===================================================
// UP TOOLBAR

void MainWindow::on_wtmove_clicked()
{
    this->disableTool();
    ui->wtmove->setChecked(true);
    ui->glwidget->enableTool(WTMOVE);
}

void MainWindow::on_wtrotate_clicked()
{
    this->disableTool();
    ui->wtrotate->setChecked(true);
    ui->glwidget->enableTool(WTROTATE);
}

void MainWindow::on_wtscale_clicked()
{
    this->disableTool();
    ui->wtscale->setChecked(true);
    ui->glwidget->enableTool(WTSCALE);
}

void MainWindow::on_redo_clicked()
{
    m_model->subdivide();
    //ui->glwidget->resetView();
}

void MainWindow::on_initCube_clicked()
{
    this->disableTool();
    if(ui->widgetValidate->isVisible()) {
        on_pushValid_clicked();
    }
    ui->glwidget->selectModel(NULL);

    m_model = new MCube();
    ui->widgetDepth->setVisible(true);
    ui->widgetHeight->setVisible(true);
    ui->widgetWidth->setVisible(true);
    ui->widgetValidate->setVisible(true);
    ui->pushCancel->setVisible(true);
    ui->pushValid->setVisible(true);
    ui->pushRemplace->setVisible(false);
    ui->widgetSubdivide->setVisible(true);
    ui->widgetName->setVisible(true);
    ui->glwidget->addmodel(m_model);

    ui->spinBoxDepth->setValue(5.0);
    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxWidth->setValue(5.0);
    ui->sliderSubdivide->setValue(1);
    ui->textEditName->setText("NewCube");

    connect(ui->spinBoxDepth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxWidth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->sliderSubdivide, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));
}

void MainWindow::on_initSphere_clicked()
{
    this->disableTool();
    if(ui->widgetValidate->isVisible()) {
        on_pushValid_clicked();
    }
    ui->glwidget->selectModel(NULL);

    //ui->widgetradius->setVisible(true);
    ui->widgetValidate->setVisible(true);
}

// ===================================================
// MENU FILE

void MainWindow::on_actionNewProject_triggered()
{
    ui->glwidget->clear();
    this->disableTool();
    this->hideDialog();
}


void MainWindow::on_actionNewCube_triggered()
{
    on_initCube_clicked();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"Choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
}

void MainWindow::on_actionSave_as_triggered()
{

}

// ===================================================
// MENU VIEW

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

// ===================================================
// MENU HELP

void MainWindow::on_actionAbout_triggered()
{
   QMessageBox::information(this, "A propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER Silvère, LAMEIRA Yannick, PELADAN Cécile");
}

// ===================================================
// RIGHT PANEL

void MainWindow::on_pushCancel_clicked()
{
    this->hideDialog();
    ui->glwidget->selectModel(NULL);
    ui->glwidget->removemodel();
}

void MainWindow::on_pushValid_clicked()
{
    this->hideDialog();
    ui->glwidget->selectModel(m_model);

    m_model->setName(ui->textEditName->text());

    /**Ne pas supprimer*/
    QPushButton* button = new QPushButton(m_model->getName());
    m_modelList.insert(button, m_model);
    /**/

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(show_param()));
    ui->controleListModel->addWidget(button);
}

// ===================================================
// MEMBER FUNCTIONS

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->glwidget->keyPressEvent(event);
}

void MainWindow::updateLastModel() {
    m_model->setWidth(ui->spinBoxWidth->value());
    m_model->setHeight(ui->spinBoxHeight->value());
    m_model->setDepth(ui->spinBoxDepth->value());
}

void MainWindow::disableTool()
{
    ui->ltadd->setChecked(false);
    ui->ltsmooth->setChecked(false);
    ui->ltmove->setChecked(false);
    ui->ltinflate->setChecked(false);
    ui->ltpinch->setChecked(false);

    ui->gtmove->setChecked(false);
    ui->gtrotate->setChecked(false);
    ui->gtscale->setChecked(false);

    ui->wtmove->setChecked(false);
    ui->wtrotate->setChecked(false);
    ui->wtscale->setChecked(false);

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

void MainWindow::show_param()
{
    /*Récupération de l'émetteur du slot, afin d'associer le button et le modèle*/
    QObject * emetteur = sender();
    QPushButton * sender = qobject_cast<QPushButton*>(emetteur);

    m_model = m_modelList.value(sender); //Modele associé
    ui->widgetName->setVisible(true);
    ui->widgetValidate->setVisible(true);
    ui->pushRemplace->setVisible(true);
    ui->pushCancel->setVisible(false);
    ui->pushValid->setVisible(false);

    /*Chargement des caractéristiques du modèle*/
    ui->glwidget->selectModel(m_model);
    ui->textEditName->setText(m_model->getName());
}

void MainWindow::on_pushRemplace_clicked()
{
    m_modelList.key(m_model)->setText(ui->textEditName->text());
    ui->widgetName->setVisible(false);
    ui->pushRemplace->setVisible(false);
}


