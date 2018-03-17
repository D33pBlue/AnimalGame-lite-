#include "e_spia.h"
#include <QtGui>

E_spia::E_spia(const QString& descri):Effetto(descri){}

E_spia* E_spia::clona()const{
    return new E_spia(*this);
}

void E_spia::onTira(Partita *p, Giocatore *g){
    if(g==p->getGiocatore()){
    QDialog* info=new QDialog(0);
    QHBoxLayout* lay=new QHBoxLayout(info);
    info->setLayout(lay);
    info->setWindowTitle("Carte dell'avversario");
    const Collettore<Carta*>*mano=p->getAi()->getMano();
    for(Collettore<Carta*>::iterator it=mano->begin();it!=mano->end();it++){
        Carta* c=*it;
        lay->addWidget(c->getPicture());
    }
    info->setGeometry(100,100,1024,500);
    info->exec();
    delete info;
    }
}

