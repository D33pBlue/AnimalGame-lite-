#ifndef ESITO_H
#define ESITO_H

#include <QDialog>

namespace Ui {
class Esito;
}

class Esito : public QDialog
{
    Q_OBJECT

public:
    explicit Esito(QWidget *parent = 0,int ptiAi =0,int ptiG =0);
    ~Esito();

private:
    Ui::Esito *ui;
    int pAi,pG;
};

#endif // ESITO_H
