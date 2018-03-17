#include "errorecaricamento.h"
#include "ui_errorecaricamento.h"

ErroreCaricamento::ErroreCaricamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErroreCaricamento)
{
    ui->setupUi(this);
    ui->textBrowser->setText(QString::fromUtf8("Si è verificato un errore nel tentativo di accedere alle risorse. Verificare che sia presente una sottocartella \"Risorse\" all'interno della cartella in cui si trova l'applicazione."));
    setWindowTitle("AnimalGame");
}

ErroreCaricamento::~ErroreCaricamento()
{
    delete ui;
}
