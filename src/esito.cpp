#include "esito.h"
#include "ui_esito.h"

Esito::Esito(QWidget *parent,int ptiAi,int ptiG) :
    QDialog(parent),
    ui(new Ui::Esito),pAi(ptiAi),pG(ptiG)
{
    ui->setupUi(this);
    setWindowTitle("AnimalGame");
    if(pG>pAi){
        ui->pic->setPixmap(QPixmap("Risorse/Immagini/vittoria.jpg"));
        ui->pic->setScaledContents(true);
        ui->textBrowser->setPlainText(QString("Hai battuto il computer per ")+QString::number(pG)+QString(" a ")+QString::number(pAi));
    }else if(pG==pAi){
        ui->textBrowser->setPlainText(QString("Hai pareggiato con il computer ")+QString::number(pG)+QString(" a ")+QString::number(pAi));
    }else{
        ui->pic->setScaledContents(true);
        ui->pic->setPixmap(QPixmap("Risorse/Immagini/loser.jpg"));
        ui->textBrowser->setPlainText(QString("Sei stato battuto dal computer per ")+QString::number(pG)+QString(" a ")+QString::number(pAi));
    }
}

Esito::~Esito()
{
    delete ui;
}
