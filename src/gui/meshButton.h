#ifndef MESHBUTTON_H
#define MESHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QString>
#include <QObject>

class MeshButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MeshButton(QString text, QWidget *parent = 0);
    explicit MeshButton(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);

signals:
    void clickedLeft();
    void clickedRight();
};

#endif // MESHBUTTON_H
