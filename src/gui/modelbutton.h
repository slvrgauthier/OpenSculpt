#ifndef MODELBUTTON_H
#define MODELBUTTON_H
#include <QPushButton>
#include <QMouseEvent>
#include <QObject>

class ModelButton : public QPushButton
{
    Q_OBJECT
public:
    ModelButton(QString m_texte, QWidget *parent = 0);
    ModelButton(QWidget* parent = 0);
    ~ModelButton();

protected:

    void mousePressEvent(QMouseEvent * event);

signals:
    void clicRight();
};

#endif // MODELBUTTON_H
