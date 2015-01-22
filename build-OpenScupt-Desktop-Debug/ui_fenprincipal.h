/********************************************************************************
** Form generated from reading UI file 'fenprincipal.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPAL_H
#define UI_FENPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtOpenGL/QGLWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtOpenGL/QGLWidget"

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
    QGLWidget *widgetfenetre;
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
            FenPrincipal->setObjectName(QStringLiteral("FenPrincipal"));
        FenPrincipal->resize(501, 346);
        actionNouveau = new QAction(FenPrincipal);
        actionNouveau->setObjectName(QStringLiteral("actionNouveau"));
        actionOuvrir = new QAction(FenPrincipal);
        actionOuvrir->setObjectName(QStringLiteral("actionOuvrir"));
        actionEnregistrer_sous = new QAction(FenPrincipal);
        actionEnregistrer_sous->setObjectName(QStringLiteral("actionEnregistrer_sous"));
        actionQuitter = new QAction(FenPrincipal);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        souris = new QAction(FenPrincipal);
        souris->setObjectName(QStringLiteral("souris"));
        souris->setCheckable(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/icon/Curseur.png"), QSize(), QIcon::Normal, QIcon::On);
        souris->setIcon(icon);
        actionDeplacer = new QAction(FenPrincipal);
        actionDeplacer->setObjectName(QStringLiteral("actionDeplacer"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/icon/quatre-fleches_318-10750.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeplacer->setIcon(icon1);
        actionRotation = new QAction(FenPrincipal);
        actionRotation->setObjectName(QStringLiteral("actionRotation"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/icon/symbole-de-rotation-a-droite_318-9143.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotation->setIcon(icon2);
        centralWidget = new QWidget(FenPrincipal);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widgetfenetre = new QGLWidget(widget_2);
        widgetfenetre->setObjectName(QStringLiteral("widgetfenetre"));
        verticalLayout_2 = new QVBoxLayout(widgetfenetre);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        horizontalLayout->addWidget(widgetfenetre);


        verticalLayout->addWidget(widget_2);

        FenPrincipal->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FenPrincipal);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 501, 22));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        FenPrincipal->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FenPrincipal);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FenPrincipal->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FenPrincipal);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FenPrincipal->setStatusBar(statusBar);
        dockWidget = new QDockWidget(FenPrincipal);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widgetbouttonconplexe = new QWidget(dockWidgetContents);
        widgetbouttonconplexe->setObjectName(QStringLiteral("widgetbouttonconplexe"));
        verticalLayout_3 = new QVBoxLayout(widgetbouttonconplexe);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        widgetsubdiviser = new QPushButton(widgetbouttonconplexe);
        widgetsubdiviser->setObjectName(QStringLiteral("widgetsubdiviser"));

        verticalLayout_3->addWidget(widgetsubdiviser);

        pushButton_3 = new QPushButton(widgetbouttonconplexe);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_3->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(widgetbouttonconplexe);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_3->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(widgetbouttonconplexe);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

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
        FenPrincipal->setWindowTitle(QApplication::translate("FenPrincipal", "OpenSculpt", 0));
        actionNouveau->setText(QApplication::translate("FenPrincipal", "Nouveau", 0));
        actionOuvrir->setText(QApplication::translate("FenPrincipal", "Ouvrir", 0));
        actionEnregistrer_sous->setText(QApplication::translate("FenPrincipal", "Enregistrer sous...", 0));
        actionQuitter->setText(QApplication::translate("FenPrincipal", "Quitter", 0));
        souris->setText(QApplication::translate("FenPrincipal", "souris", 0));
#ifndef QT_NO_TOOLTIP
        souris->setToolTip(QApplication::translate("FenPrincipal", "Selectionner", 0));
#endif // QT_NO_TOOLTIP
        actionDeplacer->setText(QApplication::translate("FenPrincipal", "deplacer", 0));
#ifndef QT_NO_TOOLTIP
        actionDeplacer->setToolTip(QApplication::translate("FenPrincipal", "Permet de d\303\251placer un objet", 0));
#endif // QT_NO_TOOLTIP
        actionRotation->setText(QApplication::translate("FenPrincipal", "rotation", 0));
#ifndef QT_NO_TOOLTIP
        actionRotation->setToolTip(QApplication::translate("FenPrincipal", "permet de tourner l'objet", 0));
#endif // QT_NO_TOOLTIP
        menuFichier->setTitle(QApplication::translate("FenPrincipal", "Fichier", 0));
        widgetsubdiviser->setText(QApplication::translate("FenPrincipal", "Subdiviser", 0));
        pushButton_3->setText(QApplication::translate("FenPrincipal", "PushButton", 0));
        pushButton_4->setText(QApplication::translate("FenPrincipal", "PushButton", 0));
        pushButton_5->setText(QApplication::translate("FenPrincipal", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipal: public Ui_FenPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPAL_H
