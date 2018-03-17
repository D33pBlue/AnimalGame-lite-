#include "campo.h"

Campo* Campo::Istanza=0;

Campo::Campo(){}

// definizione metodi di CartaGiocata

Campo::CartaGiocata::CartaGiocata(Carta *c, Giocatore *g, int m):carta(c),giocatore(g),carteMangiate(m){
    if(carteMangiate<0)carteMangiate=0;
}

bool Campo::CartaGiocata::operator ==(const CartaGiocata& c)const{
    return carta==c.carta && giocatore==c.giocatore;
}


bool Campo::CartaGiocata::operator !=(const CartaGiocata& c)const{
    return carta!=c.carta || giocatore!=c.giocatore;
}

Carta* Campo::CartaGiocata::getCarta()const{
    return carta;
}

Giocatore* Campo::CartaGiocata::getGiocatore()const{
    return giocatore;
}

int Campo::CartaGiocata::getMangiate()const{
    return carteMangiate;
}

void Campo::CartaGiocata::setGiocatore(Giocatore *g){
    giocatore=g;
}

void Campo::CartaGiocata::setMangiate(int n){
    carteMangiate=n;
}

// definizione metodi di Campo

Campo* Campo::getCampo(){
    if(!Istanza) Istanza=new Campo();
    return Istanza;
}

Campo::~Campo(){
    Collettore<CartaGiocata>::iterator it=carte.begin();
    while (it!=carte.end()) {
        removeCarta(it);
    }
}

void Campo::distruggiCampo(){
    delete Istanza;
    Istanza=0;
}

const Collettore<Campo::CartaGiocata>& Campo::getCarte() const{
    return carte;
}


void Campo::addCarta(Carta *c, Giocatore *g, int p){
    carte.insert(CartaGiocata(c,g,p));
}

void Campo::removeCarta(Collettore<CartaGiocata>::iterator &it){
    Carta* c=carte.estrai(it).getCarta();
    delete c;
}

Campo::CartaGiocata Campo::estrai(Collettore<CartaGiocata>::iterator &it){
    return carte.estrai(it);
}


