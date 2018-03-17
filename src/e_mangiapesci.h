#ifndef E_MANGIAPESCI_H
#define E_MANGIAPESCI_H

#include "effetto.h"
#include <QtCore>


class E_mangiaPesci:public Effetto
{
public:
    E_mangiaPesci(const QString&);
    virtual E_mangiaPesci* clona() const;
    virtual void onTira(Partita*,Giocatore*);
};

#endif // E_MANGIAPESCI_H
