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

// ===================================================
// LEFT PANEL

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
    ui->redo->setChecked(false);
    m_model->subdivide();
    //ui->glwidget->resetView();
}

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
    ui->sliderSubdivide->setValue(1); // Niveau de subdivision plutôt
    ui->textEditName->setText("NewCube");

    connect(ui->spinBoxDepth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxHeight, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->spinBoxWidth, SIGNAL(valueChanged(double)),this, SLOT(updateLastModel()));
    connect(ui->sliderSubdivide, SIGNAL(valueChanged(int)),this, SLOT(updateLastModel()));

}

void MainWindow::on_initSphere_clicked()
{
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

void MainWindow::on_actionNewObject_triggered()
{
    //ui->glwidget->clear(); RECODE : sous-menu avec cube, sphere...etc
}

void MainWindow::on_actionNewCube_triggered()
{
    on_initCube_clicked();
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this,"choix du ficher", "/Users/Yann/Documents/Programmation/OpenScupt/Enregistrement");
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
   QMessageBox::information(this, "a propos", "Ce logiciel a été conçu dans un but pédagogique par : GAUTHIER, LAMEIRA, PELADAN");
}

// ===================================================
// RIGHT PANEL

void MainWindow::on_pushCancel_clicked()
{
    this->hideDialog();
    ui->glwidget->removemodel();
}

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
    ui->gtmove->setChecked(false);
    ui->gtrotate->setChecked(false);
    ui->redo->setChecked(false);
    ui->gtscale->setChecked(false);
    ui->wtrotate->setChecked(false);
    ui->wtscale->setChecked(false);
    ui->wtmove->setChecked(false);

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
