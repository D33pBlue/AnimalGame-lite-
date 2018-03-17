#ifndef REGOLAMENTO_H
#define REGOLAMENTO_H

#include <QDialog>

namespace Ui {
class Regolamento;
}

class Regolamento : public QDialog
{
    Q_OBJECT

public:
    explicit Regolamento(QWidget *parent = 0);
    ~Regolamento();

private:
    Ui::Regolamento *ui;
};

#endif // REGOLAMENTO_H
