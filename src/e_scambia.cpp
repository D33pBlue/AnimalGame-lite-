#include "e_scambia.h"
#include <QVector>
#include "ai.h"
#include "giocatore.h"

#include <iostream>
using namespace std;

E_scambia::E_scambia(const QString& desc):Effetto(desc){}

E_scambia* E_scambia::clona()const{
    return new E_scambia(*this);
}

void E_scambia::onTira(Partita*p,Giocatore *){
    QVector<Carta*>carte;
    Giocatore*ai=p->getAi();
    Giocatore* g=p->getGiocatore();
    while (ai->getSizeMano()>0) {
        carte.append(ai->estraiMano(ai->getMano()->begin()));
    }
    while (g->getSizeMano()>0) {
        ai->addCartaMano(g->estraiMano(g->getMano()->begin()));
    }
    for(int i=0;i<carte.size();i++){
        g->addCartaMano(carte.at(i));
    }
}

