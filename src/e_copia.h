#ifndef E_COPIA_H
#define E_COPIA_H

#include "effetto.h"

class E_copia : public Effetto
{
public:
    E_copia(const QString&);
    virtual E_copia* clona()const;
    virtual void onTira(Partita*,Giocatore*);
};

#endif // E_COPIA_H
