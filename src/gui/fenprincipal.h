#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include <QMainWindow>
#include <QFileDialog>

#include "gui/initialisationmodele.h"

namespace Ui {
class FenPrincipal;
}

class FenPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenPrincipal(QWidget *parent = 0);
    ~FenPrincipal();

private slots:
    void on_actionOuvrir_triggered();
    void on_actionNouveau_triggered();

private:
    Ui::FenPrincipal *ui;
};

#endif // FENPRINCIPAL_H
