#ifndef AI_H
#define AI_H

#include "giocatore.h"

class Partita;

class Ai:public Giocatore
{
protected:
    virtual iterator_c trovaCartaDaTirare(Partita*)const;
public:
    Ai(int _punti =0);
    virtual void agisci(Partita*);
};

//#include "partita.h"

#endif // AI_H
