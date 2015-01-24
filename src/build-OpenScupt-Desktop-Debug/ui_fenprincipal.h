/********************************************************************************
** Form generated from reading UI file 'fenprincipal.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPAL_H
#define UI_FENPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_FenPrincipal
{
public:
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionEnregistrer_sous;
    QAction *actionQuitter;
    QAction *souris;
    QAction *actionDeplacer;
    QAction *actionRotation;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    GLWidget *widgetfenetre;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetbouttonconplexe;
    QVBoxLayout *verticalLayout_3;
    QPushButton *widgetsubdiviser;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *FenPrincipal)
    {
        if (FenPrincipal->objectName().isEmpty())
            FenPrincipal->setObjectName(QString::fromUtf8("FenPrincipal"));
        FenPrincipal->resize(501, 346);
        actionNouveau = new QAction(FenPrincipal);
        actionNouveau->setObjectName(QString::fromUtf8("actionNouveau"));
        actionOuvrir = new QAction(FenPrincipal);
        actionOuvrir->setObjectName(QString::fromUtf8("actionOuvrir"));
        actionEnregistrer_sous = new QAction(FenPrincipal);
        actionEnregistrer_sous->setObjectName(QString::fromUtf8("actionEnregistrer_sous"));
        actionQuitter = new QAction(FenPrincipal);
        actionQuitter->setObjectName(QString::fromUtf8("actionQuitter"));
        souris = new QAction(FenPrincipal);
        souris->setObjectName(QString::fromUtf8("souris"));
        souris->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/icon/Curseur.png"), QSize(), QIcon::Normal, QIcon::On);
        souris->setIcon(icon);
        actionDeplacer = new QAction(FenPrincipal);
        actionDeplacer->setObjectName(QString::fromUtf8("actionDeplacer"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/new/icon/quatre-fleches_318-10750.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeplacer->setIcon(icon1);
        actionRotation = new QAction(FenPrincipal);
        actionRotation->setObjectName(QString::fromUtf8("actionRotation"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/new/icon/symbole-de-rotation-a-droite_318-9143.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotation->setIcon(icon2);
        centralWidget = new QWidget(FenPrincipal);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widgetfenetre = new GLWidget(widget_2);
        widgetfenetre->setObjectName(QString::fromUtf8("widgetfenetre"));
        verticalLayout_2 = new QVBoxLayout(widgetfenetre);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        horizontalLayout->addWidget(widgetfenetre);


        verticalLayout->addWidget(widget_2);

        FenPrincipal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FenPrincipal);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 501, 22));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        FenPrincipal->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FenPrincipal);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        FenPrincipal->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FenPrincipal);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FenPrincipal->setStatusBar(statusBar);
        dockWidget = new QDockWidget(FenPrincipal);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widgetbouttonconplexe = new QWidget(dockWidgetContents);
        widgetbouttonconplexe->setObjectName(QString::fromUtf8("widgetbouttonconplexe"));
        verticalLayout_3 = new QVBoxLayout(widgetbouttonconplexe);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widgetsubdiviser = new QPushButton(widgetbouttonconplexe);
        widgetsubdiviser->setObjectName(QString::fromUtf8("widgetsubdiviser"));

        verticalLayout_3->addWidget(widgetsubdiviser);

        pushButton_3 = new QPushButton(widgetbouttonconplexe);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widgetbouttonconplexe);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widgetbouttonconplexe);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        verticalLayout_3->addWidget(pushButton_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_4->addWidget(widgetbouttonconplexe);

        dockWidget->setWidget(dockWidgetContents);
        FenPrincipal->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);

        menuBar->addAction(menuFichier->menuAction());
        menuFichier->addAction(actionNouveau);
        menuFichier->addAction(actionOuvrir);
        menuFichier->addAction(actionEnregistrer_sous);
        menuFichier->addAction(actionQuitter);
        mainToolBar->addAction(souris);
        mainToolBar->addAction(actionDeplacer);
        mainToolBar->addAction(actionRotation);

        retranslateUi(FenPrincipal);
        QObject::connect(actionQuitter, SIGNAL(triggered()), FenPrincipal, SLOT(close()));

        QMetaObject::connectSlotsByName(FenPrincipal);
    } // setupUi

    void retranslateUi(QMainWindow *FenPrincipal)
    {
        FenPrincipal->setWindowTitle(QApplication::translate("FenPrincipal", "OpenSculpt", 0, QApplication::UnicodeUTF8));
        actionNouveau->setText(QApplication::translate("FenPrincipal", "Nouveau", 0, QApplication::UnicodeUTF8));
        actionOuvrir->setText(QApplication::translate("FenPrincipal", "Ouvrir", 0, QApplication::UnicodeUTF8));
        actionEnregistrer_sous->setText(QApplication::translate("FenPrincipal", "Enregistrer sous...", 0, QApplication::UnicodeUTF8));
        actionQuitter->setText(QApplication::translate("FenPrincipal", "Quitter", 0, QApplication::UnicodeUTF8));
        souris->setText(QApplication::translate("FenPrincipal", "souris", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        souris->setToolTip(QApplication::translate("FenPrincipal", "Selectionner", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeplacer->setText(QApplication::translate("FenPrincipal", "deplacer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeplacer->setToolTip(QApplication::translate("FenPrincipal", "Permet de d\303\251placer un objet", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRotation->setText(QApplication::translate("FenPrincipal", "rotation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRotation->setToolTip(QApplication::translate("FenPrincipal", "permet de tourner l'objet", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFichier->setTitle(QApplication::translate("FenPrincipal", "Fichier", 0, QApplication::UnicodeUTF8));
        widgetsubdiviser->setText(QApplication::translate("FenPrincipal", "Subdiviser", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("FenPrincipal", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("FenPrincipal", "PushButton", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("FenPrincipal", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipal: public Ui_FenPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPAL_H
