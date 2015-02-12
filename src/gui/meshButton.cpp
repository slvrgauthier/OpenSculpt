#include "gui/meshButton.h"

MeshButton::MeshButton(QWidget *parent) : QPushButton(parent) {}
MeshButton::MeshButton(QString text, QWidget *parent) : QPushButton(text, parent) {}

void MeshButton::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::RightButton) {
        emit clickedRight();
    }
    if(event->button() == Qt::LeftButton) {
        emit clickedLeft();
    }
}

void MeshButton::mouseDoubleClickEvent(QMouseEvent * event) {
    if(event->button() == Qt::LeftButton) {
        emit clickedRight();
    }
}
