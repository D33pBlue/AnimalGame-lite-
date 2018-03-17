#ifndef ERRORECARICAMENTO_H
#define ERRORECARICAMENTO_H

#include <QDialog>

namespace Ui {
class ErroreCaricamento;
}

class ErroreCaricamento : public QDialog
{
    Q_OBJECT

public:
    explicit ErroreCaricamento(QWidget *parent = 0);
    ~ErroreCaricamento();

private:
    Ui::ErroreCaricamento *ui;
};

#endif // ERRORECARICAMENTO_H
