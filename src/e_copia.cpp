#include "e_copia.h"
#include <stdlib.h>
#include <time.h>

E_copia::E_copia(const QString& desc):Effetto(desc){}

E_copia* E_copia::clona()const{
    return new E_copia(*this);
}

void E_copia::onTira(Partita *p, Giocatore *g){
    srand(time(0));
    const Collettore<Campo::CartaGiocata>& campo=p->getCampo();
    Collettore<Campo::CartaGiocata>::iterator it=campo.begin();
    if(it==campo.end())return;
    while (it!=campo.end() && rand()%2) {
        it++;
    }
    if(it==campo.end())it=campo.begin();
    Campo::CartaGiocata c=*it;
    g->addCartaMano(c.getCarta()->clona());
}

