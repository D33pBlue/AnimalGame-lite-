#include "e_togli_avv.h"

E_togli_avv::E_togli_avv(const QString& d):Effetto(d){}

E_togli_avv* E_togli_avv::clona()const{
    return new E_togli_avv(*this);
}

void E_togli_avv::onTira(Partita *p, Giocatore *g){
    Giocatore* avv=p->getAi();
    if(g==p->getAi())avv=p->getGiocatore();
    const Collettore<Campo::CartaGiocata> &campo=p->getCampo();
    Collettore<Campo::CartaGiocata>::iterator it=campo.begin();
    while (it!=campo.end()) {
        Campo::CartaGiocata c=*it;
        if(c.getGiocatore()==avv){
            p->togliDalCampo(it);
        }
        it++;
    }
}
