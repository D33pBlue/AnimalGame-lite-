#ifndef MAGIA_H
#define MAGIA_H

#include <QtCore>
#include <QWidget>
#include "carta.h"
#include "effetto.h"
#include "piccarta.h"

class Magia : public Carta
{
private:
    Effetto* effetto;
public:
    Magia(unsigned int _id=0,const QString& _nome="");
    Magia(const Magia&);
    virtual ~Magia();
    Magia& operator=(const Magia&);
    //operatore uguaglianza ereditato
    void setEffetto(Effetto* e);
    virtual bool mangia(const Carta &) const;
    virtual void onTira(Partita*,Giocatore*);
    virtual PicCarta* getPicture()const;
    virtual Carta* clona() const;
};

#endif // MAGIA_H
