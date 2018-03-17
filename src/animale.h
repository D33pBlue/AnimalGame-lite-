#ifndef ANIMALE_H
#define ANIMALE_H

#include <QtCore>
#include <QWidget>
#include "carta.h"
#include "piccarta.h"

class Animale : public Carta
{

private:
    unsigned int attacco,resistenza,nemici;

public:
    Animale(unsigned int _id=0,const QString& _nome="",Tipo _tipo=NT,
            unsigned int att=0,unsigned int res=0);
    //Animale(const Animale&); versione standard
    //virtual ~Animale(); versione standard
    //Animale& operator=(const Animale&); in versione standard
    //bool operator ==(const Animale&)const; ereditato
    //bool operator !=(const Animale&)const; ereditato
    unsigned int getResistenza()const;
    unsigned int getAttacco()const;
    bool haNemico(Tipo)const;
    void aggiungiNemico(Tipo);
    virtual bool mangia(const Carta&)const;
    virtual void onTira(Partita*,Giocatore*);
    virtual PicCarta *getPicture()const;
    virtual Carta* clona() const;
};

#endif // ANIMALE_H
