#include "gui/mainWindow.h"
#include "ui_mainWindow.h"
#include <QMessageBox>
#include "gui/glwidget.h"
#include "mesh/MeshManager.h"
#include "mesh/functions.h"
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
    this->on_actionNewProject_triggered();
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

void MainWindow::on_debug_clicked()
{
    QMessageBox::information(this,"test","Rentrer dans le mode debug");
    //m_mesh->TEST();
}

// ===================================================
// UP TOOLBAR

void MainWindow::on_select_clicked() { this->disableTool(); }

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
    ui->redo->setEnabled(true);
    ui->undo->setEnabled(false);
}

void MainWindow::on_wtscale_clicked()
{
    this->disableTool();
    ui->wtscale->setChecked(true);
    ui->glwidget->enableTool(WTSCALE);
}

void MainWindow::on_undo_clicked()
{
    ui->glwidget->undo();
}

void MainWindow::on_redo_clicked()
{
    ui->glwidget->redo();
}

void MainWindow::on_subdivide_clicked()
{
    MeshProcessing::subdivide(m_mesh);
}

void MainWindow::on_decimate_clicked()
{
    MeshProcessing::decimate(m_mesh);
}

void MainWindow::on_init() {
    this->disableTool();
    if(ui->pushValid->isVisible()) {
        on_pushValid_clicked();
    }
    ui->glwidget->selectMesh(NULL);

    m_mesh = new Mesh();
    m_mesh->setName("Mesh");

    ui->widgetValidate->setVisible(true);
    ui->pushRemplace->setVisible(false);
    ui->pushCancel->setVisible(true);
    ui->pushValid->setVisible(true);
    ui->widgetSubdivide->setVisible(true);
    ui->widgetName->setVisible(true);
    ui->glwidget->addMesh(m_mesh);

    ui->sliderDiscretization->setValue(ui->sliderDiscretization->minimum());
    ui->textEditName->setText(m_mesh->getName());
}

void MainWindow::on_initCube_clicked()
{
    this->on_init();

    ui->widgetDepth->setVisible(true);
    ui->widgetHeight->setVisible(true);
    ui->widgetWidth->setVisible(true);

    ui->spinBoxDepth->setValue(5.0);
    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxWidth->setValue(5.0);

    updateCube();

    connect(ui->spinBoxDepth,         SIGNAL(valueChanged(double)), this, SLOT(updateCube()));
    connect(ui->spinBoxHeight,        SIGNAL(valueChanged(double)), this, SLOT(updateCube()));
    connect(ui->spinBoxWidth,         SIGNAL(valueChanged(double)), this, SLOT(updateCube()));
    connect(ui->sliderDiscretization, SIGNAL(valueChanged(int)),    this, SLOT(updateCube()));
}

void MainWindow::on_initSphere_clicked()
{
    this->on_init();

    ui->widgetRadius->setVisible(true);

    ui->spinBoxRadius->setValue(5.0);

    updateSphere();

    connect(ui->spinBoxRadius,        SIGNAL(valueChanged(double)), this, SLOT(updateSphere()));
    connect(ui->sliderDiscretization, SIGNAL(valueChanged(int)),    this, SLOT(updateSphere()));
}

void MainWindow::on_initCylinder_clicked()
{
    this->on_init();

    ui->widgetHeight->setVisible(true);
    ui->widgetRadius->setVisible(true);

    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxRadius->setValue(1.0);

    updateCylinder();

    connect(ui->spinBoxHeight,        SIGNAL(valueChanged(double)), this, SLOT(updateCylinder()));
    connect(ui->spinBoxRadius,        SIGNAL(valueChanged(double)), this, SLOT(updateCylinder()));
    connect(ui->sliderDiscretization, SIGNAL(valueChanged(int)),    this, SLOT(updateCylinder()));
}

void MainWindow::on_initCone_clicked()
{
    this->on_init();

    ui->widgetHeight->setVisible(true);
    ui->widgetRadius->setVisible(true);

    ui->spinBoxHeight->setValue(5.0);
    ui->spinBoxRadius->setValue(2.0);

    updateCone();

    connect(ui->spinBoxHeight,        SIGNAL(valueChanged(double)), this, SLOT(updateCone()));
    connect(ui->spinBoxRadius,        SIGNAL(valueChanged(double)), this, SLOT(updateCone()));
    connect(ui->sliderDiscretization, SIGNAL(valueChanged(int)),    this, SLOT(updateCone()));
}

void MainWindow::on_initTorus_clicked()
{
    this->on_init();

    ui->widgetRadius->setVisible(true);

    ui->spinBoxRadius->setValue(3.0);

    updateTorus();

    connect(ui->spinBoxHeight,        SIGNAL(valueChanged(double)), this, SLOT(updateTorus()));
    connect(ui->spinBoxRadius,        SIGNAL(valueChanged(double)), this, SLOT(updateTorus()));
    connect(ui->sliderDiscretization, SIGNAL(valueChanged(int)),    this, SLOT(updateTorus()));
}

// ===================================================
// MENU FILE

void MainWindow::on_actionNewProject_triggered()
{
    this->disableTool();
    this->hideDialog();

    qDeleteAll(m_meshList.keys());
    m_meshList.clear();

    ui->glwidget->enableTool(NOTOOL);
    ui->glwidget->selectMesh(NULL);
    ui->glwidget->clear();
    ui->glwidget->resetView();
}

void MainWindow::on_actionNewCube_triggered()
{
    on_initCube_clicked();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"Choix du ficher", "./");
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

void MainWindow::on_pushRemplace_clicked()
{
    this->hideDialog();
    m_mesh->setName(ui->textEditName->text());
    m_meshList.key(m_mesh)->setText(m_mesh->getName());
}

void MainWindow::on_pushCancel_clicked()
{
    this->hideDialog();
    ui->glwidget->selectMesh(NULL);
    ui->glwidget->removeMesh(m_mesh);
}

void MainWindow::on_pushValid_clicked()
{
    this->hideDialog();
    ui->glwidget->selectMesh(m_mesh);

    m_mesh->setName(ui->textEditName->text());

    QPushButton *button = new QPushButton(m_mesh->getName());
    m_meshList.insert(button, m_mesh);

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(showDialog()));
    ui->controleListModel->addWidget(button);
}

void MainWindow::on_pushDelete_clicked()
{
    QPushButton *button = m_meshList.key(m_mesh);
    button->deleteLater();
    ui->glwidget->removeMesh(m_mesh);
    ui->glwidget->selectMesh(NULL);
    this->hideDialog();
}

void MainWindow::on_pushDuplicate_clicked()
{
    /*this->on_init();
   // m_mesh = Mesh::copyMesh(m_mesh);
    ui->glwidget->selectMesh(m_mesh);
    ui->textEditName->setText(m_mesh->getName());*/
}

// ===================================================
// MEMBER FUNCTIONS

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    ui->glwidget->mouseMoveEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ui->glwidget->keyPressEvent(event);
}

void MainWindow::updateCube() {
    m_mesh->makeCube(ui->spinBoxWidth->value(), ui->spinBoxHeight->value(), ui->spinBoxDepth->value(), ui->sliderDiscretization->value());
}

void MainWindow::updateSphere() {
    m_mesh->makeSphere(ui->spinBoxRadius->value(), ui->sliderDiscretization->value());
}

void MainWindow::updateCylinder() {
    m_mesh->makeCylinder(ui->spinBoxHeight->value(), ui->spinBoxRadius->value(), ui->sliderDiscretization->value());
}

void MainWindow::updateCone() {
    m_mesh->makeCone(ui->spinBoxHeight->value(), 0., ui->spinBoxRadius->value(), ui->sliderDiscretization->value()); // RECODE : deux rayons
}

void MainWindow::updateTorus() {
    m_mesh->makeTorus(ui->spinBoxRadius->value(), ui->spinBoxRadius->value() / 4., ui->sliderDiscretization->value()); // RECODE : deux rayons
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
    ui->widgetWidth->setVisible(false);
    ui->widgetHeight->setVisible(false);
    ui->widgetDepth->setVisible(false);
    ui->widgetRadius->setVisible(false);

    ui->widgetValidate->setVisible(false);
    ui->widgetSubdivide->setVisible(false);
    ui->widgetName->setVisible(false);
    ui->pushRemplace->setVisible(false);
    ui->pushDelete->setVisible(false);
    ui->pushDuplicate->setVisible(false);
}

void MainWindow::showDialog()
{
    if(ui->pushValid->isVisible()) {
        on_pushValid_clicked();
    }

    /*Récupération de l'émetteur du slot, afin d'associer le button et le modèle*/
    QObject * emetteur = sender();
    QPushButton * sender = qobject_cast<QPushButton*>(emetteur);

    m_mesh = m_meshList.value(sender); //Modele associé

    ui->widgetName->setVisible(true);
    ui->widgetValidate->setVisible(true);
    ui->pushRemplace->setVisible(true);
    ui->pushDelete->setVisible(true);
    //ui->pushDuplicate->setVisible(true);
    ui->pushCancel->setVisible(false);
    ui->pushValid->setVisible(false);

    /*Chargement des caractéristiques du modèle*/
    ui->glwidget->selectMesh(m_mesh);
    ui->textEditName->setText(m_mesh->getName());
}
