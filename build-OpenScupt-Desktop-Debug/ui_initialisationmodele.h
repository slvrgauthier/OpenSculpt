/********************************************************************************
** Form generated from reading UI file 'initialisationmodele.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALISATIONMODELE_H
#define UI_INITIALISATIONMODELE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qopenglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_InitialisationModele
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *Nomdelinfo;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QTableView *choixmodele;
    QOpenGLWidget *afficheModele;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *annuler;
    QPushButton *suivant;

    void setupUi(QDialog *InitialisationModele)
    {
        if (InitialisationModele->objectName().isEmpty())
            InitialisationModele->setObjectName(QStringLiteral("InitialisationModele"));
        InitialisationModele->resize(400, 300);
        verticalLayout = new QVBoxLayout(InitialisationModele);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        Nomdelinfo = new QLabel(InitialisationModele);
        Nomdelinfo->setObjectName(QStringLiteral("Nomdelinfo"));

        verticalLayout->addWidget(Nomdelinfo);

        widget = new QWidget(InitialisationModele);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        choixmodele = new QTableView(widget);
        choixmodele->setObjectName(QStringLiteral("choixmodele"));
        choixmodele->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_2->addWidget(choixmodele);

        afficheModele = new QOpenGLWidget(widget);
        afficheModele->setObjectName(QStringLiteral("afficheModele"));
        afficheModele->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(afficheModele);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(InitialisationModele);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        annuler = new QPushButton(widget_2);
        annuler->setObjectName(QStringLiteral("annuler"));

        horizontalLayout->addWidget(annuler);

        suivant = new QPushButton(widget_2);
        suivant->setObjectName(QStringLiteral("suivant"));

        horizontalLayout->addWidget(suivant);


        verticalLayout->addWidget(widget_2);


        retranslateUi(InitialisationModele);
        QObject::connect(annuler, SIGNAL(clicked()), InitialisationModele, SLOT(reject()));

        QMetaObject::connectSlotsByName(InitialisationModele);
    } // setupUi

    void retranslateUi(QDialog *InitialisationModele)
    {
        InitialisationModele->setWindowTitle(QApplication::translate("InitialisationModele", "Dialog", 0));
        Nomdelinfo->setText(QApplication::translate("InitialisationModele", "Choisissez le mod\303\250le \303\240 importer :", 0));
        annuler->setText(QApplication::translate("InitialisationModele", "Annuler", 0));
        suivant->setText(QApplication::translate("InitialisationModele", "Suivant", 0));
    } // retranslateUi

};

namespace Ui {
    class InitialisationModele: public Ui_InitialisationModele {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALISATIONMODELE_H
