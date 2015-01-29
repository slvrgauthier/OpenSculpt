#include "tool/GTMove.h"
#include <QDebug>

void GTMove::action(Model *model, QVector3D position, float dx, float dy)
{
    qDebug() << "GTMove action !";
    QVector3D currentPoint;
    for(int i=0 ; i < model->getSize() ; ++i) {
        currentPoint = model->getVertex(i);
        currentPoint.setX(currentPoint.x()+dx);//Normaliser dx et dy
        currentPoint.setY(currentPoint.y()+dy);
        currentPoint.setZ(currentPoint.z()+0);
        model->setVertex(i, currentPoint);
    }
    model->update();
}
