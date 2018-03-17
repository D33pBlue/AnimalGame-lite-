#ifndef ANIMALECE_H
#define ANIMALECE_H

#include <QtCore>
#include <QWidget>
#include "animale.h"
#include "effetto.h"

class AnimaleCE: public Animale
{

private:
    Effetto* effetto;
public:
    AnimaleCE(unsigned int _id=0,const QString& _nome="",Tipo _tipo=NT,
              unsigned int att=0,unsigned int res=0);
    AnimaleCE(const AnimaleCE&);
    virtual ~AnimaleCE();
    AnimaleCE& operator=(const AnimaleCE&);
    //bool mangia(const Carta&); ereditata
    void setEffetto(Effetto*);
    virtual void onTira(Partita*,Giocatore*);
    PicCarta* getPicture()const;
    virtual Carta* clona() const;
};

#endif // ANIMALECE_H
