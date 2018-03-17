#ifndef E_TOGLI_AVV_H
#define E_TOGLI_AVV_H

#include "effetto.h"

class E_togli_avv : public Effetto
{
public:
    E_togli_avv(const QString&);
    virtual E_togli_avv* clona() const;
    virtual void onTira(Partita *, Giocatore *);
};

#endif // E_TOGLI_AVV_H
