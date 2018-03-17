#include "e_mangiapesci.h"

E_mangiaPesci::E_mangiaPesci(const QString & desc):Effetto(desc){}

E_mangiaPesci* E_mangiaPesci::clona()const{
    return new E_mangiaPesci(*this);
}

void E_mangiaPesci::onTira(Partita*p,Giocatore* g){
     const Collettore<Campo::CartaGiocata>& carte=p->getCampo();
     for(Collettore<Campo::CartaGiocata>::iterator it=carte.begin();it!=carte.end();it++){
         Campo::CartaGiocata carta=*it;
         if(carta.getCarta()->getTipo()==pesce){
             p->togliDalCampo(it);
             if(g)g->increasePunti(1);
            }
        }
}

