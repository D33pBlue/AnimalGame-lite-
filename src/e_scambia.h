#ifndef E_SCAMBIA_H
#define E_SCAMBIA_H

#include "effetto.h"

class E_scambia : public Effetto
{
public:
    E_scambia(const QString&);
    virtual E_scambia *clona() const;
    virtual void onTira(Partita*,Giocatore*);
};

#endif // E_SCAMBIA_H
