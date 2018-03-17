#ifndef E_SPIA_H
#define E_SPIA_H

#include "effetto.h"

class E_spia :public Effetto
{
public:
    E_spia(const QString&);
    virtual E_spia* clona() const;
    virtual void onTira(Partita*,Giocatore*);
};

#endif // E_SPIA_H
