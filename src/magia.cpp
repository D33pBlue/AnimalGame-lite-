#include "magia.h"

Magia::Magia(unsigned int _id, const QString &_nome):
        Carta(_id,_nome,magia),effetto(0){}

Magia::Magia(const Magia & m): Carta(m),effetto(m.effetto->clona()){}


Magia::~Magia(){
    if(effetto){
         delete effetto;
    }
}

Magia& Magia::operator =(const Magia& m){
    if(*this!=m){
        Carta::operator=(m);
        effetto=m.effetto->clona();
    }
    return *this;
}

void Magia::setEffetto(Effetto *e){
    effetto=e;
}

bool Magia::mangia(const Carta &) const{
    return false;
}

void Magia::onTira(Partita*p,Giocatore*g){
    if(effetto)effetto->onTira(p,g);
}

PicCarta *Magia::getPicture()const{
    PicCarta* pic=new PicCarta(getId(),getNome());
    pic->setBackground(QPixmap("Risorse/Immagini/magia.jpg"),true);

    QLabel*_tipo=creaIconaTipo(pic,magia,pic->unita);
    _tipo->setGeometry(pic->w-30*pic->unita,5*pic->unita,20*pic->unita,20*pic->unita);


    QTextBrowser *descri=new QTextBrowser(pic);
    descri->setPlainText(effetto->getDescrizione());
    descri->setGeometry(5,125*pic->unita,pic->w-10,pic->h-130*pic->unita-5);
    descri->setFrameShape(QFrame::NoFrame);
    descri->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    descri->setFont(QFont("serif",8));
    descri->setStyleSheet("background-image:url(Risorse/Immagini/bgtra.png); border-radius:10px;border-style:dashed;border-width:1px;border-color:rgb(153,56,0);");
    return pic;
}

Carta* Magia::clona()const{
    return new Magia(*this);
}
