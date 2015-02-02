#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>
class myLabel : public QLabel
{
protected:

    void mousePressEvent(QMouseEvent*event);
public:
    myLabel();

private:

};

#endif // MYLABEL_H
