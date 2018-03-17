#include "carta.h"
#include "giocatore.h"
#include "partita.h"

Tipo traduciTipo(QString t){
    if(t==QString("arma"))return arma;
    if(t==QString("carnivoro"))return carnivoro;
    if(t==QString("uccello"))return uccello;
    if(t==QString("insettivoro"))return insettivoro;
    if(t==QString("pesce"))return pesce;
    if(t==QString("rettile"))return rettile;
    if(t==QString("onnivoro"))return onnivoro;
    if(t==QString("erbivoro"))return erbivoro;
    if(t==QString("insetto"))return insetto;
    if(t==QString("pianta"))return pianta;
    if(t==QString("magia"))return magia;
    return NT;
}

Carta::Carta(unsigned int _id, const QString &_nome, Tipo _tipo):id(_id),
        nome(_nome),tipo(_tipo){}

Carta::~Carta(){}

bool Carta::operator ==(const Carta& b)const{
    return id==b.id;
}

bool Carta::operator !=(const Carta& b)const{
    return id!=b.id;
}

QString Carta::getNome()const{
    return nome;
}

Tipo Carta::getTipo()const{
    return tipo;
}

unsigned int Carta::getId()const{
    return id;
}

QLabel* Carta::creaIconaTipo(QWidget *p, Tipo t,double unita)const{
    QLabel*_tipo=new QLabel(p);
    QString percorso=QString("Risorse/Immagini/Tipi/")+QString::number(t)+QString(".png");
    _tipo->setPixmap(QPixmap(percorso));
    _tipo->setScaledContents(true);
    _tipo->setMaximumSize(20*unita,20*unita);
    _tipo->setMinimumSize(10*unita,10*unita);
    return _tipo;
}
