#include "mylabel.h"
#include <qmessagebox.h>

myLabel::myLabel()
{
}
void myLabel::mousePressEvent(QMouseEvent *event)
{
    QMessageBox::warning(this,"clic",QString("tu as cliqué sur un qlabel"));


}

