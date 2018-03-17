#ifndef EFFETTO_H
#define EFFETTO_H

#include <QtCore>

class Partita;
class Giocatore;

class Effetto
{//classe astratta che verrà estesa dai veri effetti
private:
    QString descrizione;
public:
    Effetto(QString descri="");
    //costruttore di copia di default
    QString getDescrizione()const;
    virtual ~Effetto();
    virtual Effetto* clona()const=0;
    virtual void onTira(Partita*,Giocatore*)=0;
};


#include "partita.h"

Effetto* traduciEffetto(QString,QString);


#endif // EFFETTO_H
