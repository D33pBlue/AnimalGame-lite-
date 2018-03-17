#ifndef NUOVAPARTITA_H
#define NUOVAPARTITA_H

#include <QDialog>

namespace Ui {
class NuovaPartita;
}

class NuovaPartita : public QDialog
{
    Q_OBJECT

public:
    explicit NuovaPartita(QWidget *parent = 0);
    ~NuovaPartita();

private slots:
    void on_buttonBox_accepted();
signals:
    void nuova(QString);

private:
    Ui::NuovaPartita *ui;
};

#endif // NUOVAPARTITA_H
