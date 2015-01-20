#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
int main(int argv, char **args)
{
        QApplication app(argv, args);

        QPushButton subButton("Subdiviser");
        subButton.setToolTip("permet de subdiviser");

        QPushButton *selectButton = new QPushButton( "Selectionner");
        selectButton->setIcon( QIcon("Curseur.png") );
        selectButton->setToolTip("selectionne l'objet");

        QVBoxLayout layout;
        layout.addWidget(&subButton);
        layout.addWidget(selectButton);

        QWidget window;
        window.setLayout(&layout);
        window.show();
        return app.exec();
}
