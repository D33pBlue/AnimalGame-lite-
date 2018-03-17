#include "animale.h"

#include <iostream>
using namespace std;




Animale::Animale(unsigned int _id, const QString &_nome, Tipo _tipo,
                  unsigned int att, unsigned int res):
    Carta(_id,_nome,_tipo),attacco(att),resistenza(res),nemici(1){}


void Animale::aggiungiNemico(Tipo t){
    if(nemici==0)nemici=t;
    else if(nemici%t){
        nemici=nemici*t;
    }
}

bool Animale::mangia(const Carta &c) const{
    const Animale*a=dynamic_cast<const Animale*>(&c);
    //solo carte animale (o discendenti) possono essere mangiate
    if(!a)return false;
    if(!(a->haNemico(getTipo())))return false;
    return attacco>=a->resistenza;
}


unsigned int Animale::getAttacco()const{
    return attacco;
}

unsigned int Animale::getResistenza()const{
    return resistenza;
}

bool Animale::haNemico(Tipo t) const{
    return (nemici%t)==0;
}

void Animale::onTira(Partita*,Giocatore*){}



PicCarta* Animale::getPicture() const{
   PicCarta* pic=new PicCarta(getId(),getNome());
   pic->setBackground(QPixmap("Risorse/Immagini/animale.jpg"),true);

   QLabel*_tipo=creaIconaTipo(pic,getTipo(),pic->unita);
   _tipo->setGeometry(pic->w-30*pic->unita,5*pic->unita,20*pic->unita,20*pic->unita);

   QString info=QString("Res: ")+QString::number(getResistenza())+QString(" ~ Att: ")+
           QString::number(getAttacco());

   QLabel* inf=new QLabel(info,pic);//distruzione con pic
   inf->setFont(QFont("Helvetica",8*pic->unita,QFont::Bold));
   inf->setAlignment(Qt::AlignCenter);
   inf->setGeometry(0,125*pic->unita,pic->w,20*pic->unita);

   QWidget* nemBox=new QWidget(pic);
   QHBoxLayout* nem=new QHBoxLayout(nemBox);
   nemBox->setLayout(nem);
   nemBox->setGeometry(0,160*pic->unita,pic->w,pic->h-170*pic->unita);
   if(haNemico(carnivoro))nem->addWidget(creaIconaTipo(pic,carnivoro,pic->unita));
   if(haNemico(uccello))nem->addWidget(creaIconaTipo(pic,uccello,pic->unita));
   if(haNemico(insettivoro))nem->addWidget(creaIconaTipo(pic,insettivoro,pic->unita));
   if(haNemico(pesce))nem->addWidget(creaIconaTipo(pic,pesce,pic->unita));
   if(haNemico(rettile))nem->addWidget(creaIconaTipo(pic,rettile,pic->unita));
   if(haNemico(onnivoro))nem->addWidget(creaIconaTipo(pic,onnivoro,pic->unita));
   if(haNemico(erbivoro))nem->addWidget(creaIconaTipo(pic,erbivoro,pic->unita));
   if(haNemico(insetto))nem->addWidget(creaIconaTipo(pic,insetto,pic->unita));
   if(haNemico(pianta))nem->addWidget(creaIconaTipo(pic,pianta,pic->unita));

   return pic;
}

Carta* Animale::clona()const{
    return new Animale(*this);
}
