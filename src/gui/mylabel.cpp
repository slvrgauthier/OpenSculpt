#include "mylabel.h"
#include <qmessagebox.h>
#include <QString>
myLabel::myLabel()
{
}
void myLabel::mousePressEvent(QMouseEvent *event)
{
    QMessageBox::warning(this,"clic",QString("tu as cliqué sur un qlabel") + getId());
}

QString myLabel::getId()
{
    //recuperer l'id du modèle
    return " l'id est 1234";
}
