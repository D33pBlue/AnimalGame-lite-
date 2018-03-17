#include "nuovapartita.h"
#include "ui_nuovapartita.h"

NuovaPartita::NuovaPartita(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NuovaPartita)
{
    ui->setupUi(this);
    setWindowTitle("Nuova Partita");
}

NuovaPartita::~NuovaPartita()
{
    delete ui;
}

void NuovaPartita::on_buttonBox_accepted()
{
    QString nome=ui->lineEdit->text();
    if(nome.size()<=0)nome=QString("Tu");
    emit nuova(nome);
    delete this;
}
