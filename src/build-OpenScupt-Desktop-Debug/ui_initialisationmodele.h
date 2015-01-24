/********************************************************************************
** Form generated from reading UI file 'initialisationmodele.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALISATIONMODELE_H
#define UI_INITIALISATIONMODELE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
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
            InitialisationModele->setObjectName(QString::fromUtf8("InitialisationModele"));
        InitialisationModele->resize(400, 300);
        verticalLayout = new QVBoxLayout(InitialisationModele);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Nomdelinfo = new QLabel(InitialisationModele);
        Nomdelinfo->setObjectName(QString::fromUtf8("Nomdelinfo"));

        verticalLayout->addWidget(Nomdelinfo);

        widget = new QWidget(InitialisationModele);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        choixmodele = new QTableView(widget);
        choixmodele->setObjectName(QString::fromUtf8("choixmodele"));
        choixmodele->setSelectionBehavior(QAbstractItemView::SelectRows);

        horizontalLayout_2->addWidget(choixmodele);

        afficheModele = new QOpenGLWidget(widget);
        afficheModele->setObjectName(QString::fromUtf8("afficheModele"));
        afficheModele->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(afficheModele);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(InitialisationModele);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        annuler = new QPushButton(widget_2);
        annuler->setObjectName(QString::fromUtf8("annuler"));

        horizontalLayout->addWidget(annuler);

        suivant = new QPushButton(widget_2);
        suivant->setObjectName(QString::fromUtf8("suivant"));

        horizontalLayout->addWidget(suivant);


        verticalLayout->addWidget(widget_2);


        retranslateUi(InitialisationModele);
        QObject::connect(annuler, SIGNAL(clicked()), InitialisationModele, SLOT(reject()));

        QMetaObject::connectSlotsByName(InitialisationModele);
    } // setupUi

    void retranslateUi(QDialog *InitialisationModele)
    {
        InitialisationModele->setWindowTitle(QApplication::translate("InitialisationModele", "Dialog", 0, QApplication::UnicodeUTF8));
        Nomdelinfo->setText(QApplication::translate("InitialisationModele", "Choisissez le mod\303\250le \303\240 importer :", 0, QApplication::UnicodeUTF8));
        annuler->setText(QApplication::translate("InitialisationModele", "Annuler", 0, QApplication::UnicodeUTF8));
        suivant->setText(QApplication::translate("InitialisationModele", "Suivant", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InitialisationModele: public Ui_InitialisationModele {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALISATIONMODELE_H
