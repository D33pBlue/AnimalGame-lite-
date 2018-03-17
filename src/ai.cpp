#include "ai.h"
#include "partita.h"


Ai::Ai(int _punti):Giocatore("Ai",_punti){}

iterator_c Ai::trovaCartaDaTirare(Partita *p)const{
    //intelligenza artificiale sostituibile
    const Collettore<Carta*>* mano=getMano();
    iterator_c best=mano->begin();
    int mang=0;
    for(iterator_c it=mano->begin();it!=mano->end();it++){
        int m=0;
        Carta* carta=*it;
        const Collettore<Campo::CartaGiocata>& campo=p->getCampo();
        for(Collettore<Campo::CartaGiocata>::iterator ic=campo.begin();ic!=campo.end();ic++){
            Campo::CartaGiocata cg=*ic;
            if(carta->mangia(*(cg.getCarta())))m+=1+cg.getMangiate();
        }
        if(m>mang){
            mang=m;
            best=it;
        }
    }
    return best;
}


void Ai::agisci(Partita *p){
    Giocatore::agisci(p);
    Carta* c=estraiMano(trovaCartaDaTirare(p));
    p->mettiInCampo(c,this);
}
