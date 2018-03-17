#include "arma.h"

#include "animale.h"

Arma::Arma(unsigned int _id, const QString &_nome, unsigned int att):
        Carta(_id,_nome,arma),attacco(att){}

bool Arma::mangia(const Carta &c) const{
    const Animale* a=dynamic_cast<const Animale*>(&c);
    if(!a)return false;
    return attacco>=a->getResistenza();
}


void Arma::onTira(Partita*,Giocatore*){}

PicCarta *Arma::getPicture()const{
    PicCarta* pic=new PicCarta(getId(),getNome(),true);
    pic->setBackground(QPixmap("Risorse/Immagini/arma.jpg"),true);

    QLabel*_tipo=creaIconaTipo(pic,getTipo(),pic->unita);
    _tipo->setGeometry(pic->w-30*pic->unita,5*pic->unita,20*pic->unita,20*pic->unita);

    QString info=QString("Attacco: ")+QString::number(getAttacco());

    QLabel* inf=new QLabel(info,pic);//distruzione con pic
    inf->setFont(QFont("Helvetica",10*pic->unita,QFont::Bold));
    inf->setAlignment(Qt::AlignCenter);
    inf->setGeometry(0,140*pic->unita,pic->w,40*pic->unita);
    inf->setStyleSheet("color:#ffffff;");


    return pic;
}

Carta* Arma::clona()const{
    return new Arma(*this);
}

unsigned int Arma::getAttacco()const{
    return attacco;
}
