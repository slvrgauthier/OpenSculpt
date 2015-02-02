#include "tool/GTMove.h"
#include <QDebug>

void GTMove::action(Model *model, QVector3D position, QVector3D move)
{
    qDebug() << "GTMove action !";
    QVector3D currentPoint;
    for(int i=0 ; i < model->getSize() ; ++i) {
        currentPoint = model->getVertex(i);
        currentPoint.setX(currentPoint.x()+move.x());
        currentPoint.setY(currentPoint.y()+move.y());
        currentPoint.setZ(currentPoint.z()+move.z());
        model->setVertex(i, currentPoint);
    }
    model->update();
}
