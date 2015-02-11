#include "modelbutton.h"

ModelButton::ModelButton(QWidget *parent) : QPushButton(parent)
{

}

ModelButton::ModelButton(QString m_texte, QWidget* parent) : QPushButton(m_texte, parent)
{

}

ModelButton::~ModelButton()
{

}

void ModelButton::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::RightButton)
    {
        emit clicRight();
    }
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
