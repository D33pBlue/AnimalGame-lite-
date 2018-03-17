#include "giocatore.h"
#include "partita.h"

#include <iostream>
using namespace std;


Giocatore::Giocatore(QString _nome,int _punti,QObject*parent):QObject(parent),punti(_punti),nome(_nome){}

Giocatore::~Giocatore(){
    for(iterator_c it=mazzo.begin();it!=mazzo.end();it++){
        delete (*it);//distrugge le carte
    }
    mazzo.clear();//distrugge i nodi
    for(iterator_c it=mano.begin();it!=mano.end();it++){
        delete (*it);
    }
    mano.clear();
}

void Giocatore::addCarta(Carta *c){
    mazzo.insert(c);
}

void Giocatore::addCartaMano(Carta *c){
    mano.insert(c);
}

void Giocatore::pesca()try{
    while(mano.size()<5 && mazzo.size()>0){
        iterator_c it=mazzo.begin();
        mano.insert(mazzo.estrai(it));
    }
}catch(CollettoreException){
    throw MazzoEsaurito();
}

const Collettore<Carta*>* Giocatore::getMano()const{
    return &mano;
}

Carta* Giocatore::estraiMano(const iterator_c &it){
    return mano.estrai(it);
}

Carta* Giocatore::estraiMano(unsigned int id){
    iterator_c it=mano.begin();
    while(it!=mano.end() && (*it)->getId()!=id)
        it++;
    if(it==mano.end())throw InvalidCarta();
    return mano.estrai(it);
}

void Giocatore::scarta(iterator_c &it){
    mano.remove(it);
}

void Giocatore::scarta(unsigned int id){
    iterator_c it=mano.begin();
    while(it!=mano.end() && (*it)->getId()!=id)
        it++;
    if(it==mano.end())throw InvalidCarta();
    mano.remove(it);
}

int Giocatore::getSizeMano()const{
    return mano.size();
}

int Giocatore::getSizeMazzo()const{
    return mazzo.size();
}

int Giocatore::getPunti()const{
    return punti;
}

QString Giocatore::getNome()const{
    return nome;
}

void Giocatore::increasePunti(int qnt){
    punti=punti+qnt;
}

void Giocatore::decreasePunti(int qnt){
    punti=punti-qnt;
}

void Giocatore::agisci(Partita*){
    if(mano.size()==0)pesca();
}

void Giocatore::tira(unsigned int i){
    Carta* c;
    try{c=estraiMano(i);}
    catch(InvalidCarta){
        c=estraiMano(mano.begin());
    }
    Partita::getPartita()->mettiInCampo(c,this);
}
