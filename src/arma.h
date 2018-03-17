#ifndef ARMA_H
#define ARMA_H

#include <QtCore>
#include <QWidget>
#include "carta.h"
#include "piccarta.h"

class Arma: public Carta
{
private:
    unsigned int attacco;
public:
    Arma(unsigned int _id=0,const QString& _nome="",unsigned int att=0);
    //costruttore di copia in versione standard
    //assegnazione standard
    //distruzione standard
    unsigned int getAttacco()const;
    virtual bool mangia(const Carta&)const;
    virtual void onTira(Partita*,Giocatore*);
    virtual PicCarta* getPicture()const;
    virtual Carta* clona() const;
};

#endif // ARMA_H
