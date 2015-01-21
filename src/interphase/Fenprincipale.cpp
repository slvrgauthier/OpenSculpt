#include "Fenprincipale.h"
#include <QApplication>
#include <QtGui>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>

FenPrincipale::FenPrincipale()
{
      QWidget *fenetre = new QWidget;
      setWindowTitle("OpenSculpt");
      QMdiArea *zoneCentrale = new QMdiArea;


      // Bar de Menu
      QMenu *menuFichier = menuBar()->addMenu("&Fichier");
      QMenu *menuAide=menuBar()->addMenu("&Aide");

      //Action du menu
      QAction *actionNouveau =new QAction ("&Nouveau", this);
      menuFichier->addAction(actionNouveau);

      QAction *actionOuvrir =new QAction("&Ouvrir", this);
      menuFichier->addAction(actionOuvrir);

      QAction *actionEnregistrer =new QAction("&Enregistrer sous...", this);
      menuFichier->addAction(actionEnregistrer);


      QAction *actionQuitter =new QAction("&Quitter", this);
      menuFichier->addAction(actionQuitter);

      QAction *actionAide =new QAction ("&A propos de", this);
      menuAide->addAction(actionAide);

      QVBoxLayout *layout = new QVBoxLayout;


      QPushButton *subButton = new QPushButton("Subdiviser",fenetre);
      subButton->setToolTip("permet de subdiviser");
      subButton->resize(50,20);

      QPushButton *selectButton = new QPushButton( "Selectionner",fenetre);
      selectButton->setIcon( QIcon("Curseur.png") );
      selectButton->setToolTip("selectionne l'objet");
      selectButton->resize(50,20);


      QFrame *frame=new QFrame(fenetre);
      frame->setFrameShape(QFrame::StyledPanel);

      layout->addWidget(subButton);
      layout->addWidget(selectButton);

      layout->addWidget(frame);


      fenetre->setLayout(layout);
      fenetre->show();

      QMdiSubWindow *sousFenetre_config = zoneCentrale->addSubWindow(fenetre);


      zoneCentrale->setViewMode(QMdiArea::TabbedView);

      setCentralWidget(zoneCentrale);


}



