#ifndef PARAMETRAGEMODELE_H
#define PARAMETRAGEMODELE_H

#include <QDialog>

enum TYPE
{
    CUBE,
    CYLINDRE
};
namespace Ui {
class ParametrageModele;
}

class ParametrageModele : public QDialog
{
    Q_OBJECT

public:
    explicit ParametrageModele(TYPE type, QWidget *parent = 0);
    ~ParametrageModele();

private:
    Ui::ParametrageModele *ui;
};

#endif // PARAMETRAGEMODELE_H
