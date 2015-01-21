#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include "FenPrincipale.h"

int main(int argv, char **args)
{
        QApplication app(argv, args);

        FenPrincipale fenetre;
        fenetre.show();


        return app.exec();
}
