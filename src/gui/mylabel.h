#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
#include <QString>

class myLabel : public QLabel
{
protected:

    void mousePressEvent(QMouseEvent*event);
public:
    myLabel();
    QString getId();

private:

};

#endif // MYLABEL_H
