#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <QObject>
#include <QtCore>
#include "carta.h"
#include "collettore.h"

class Partita;

typedef Collettore<Carta*>::iterator iterator_c;//iteratore di carte*

class GiocatoreException{};
class MazzoEsaurito:public GiocatoreException{};
class InvalidCarta:public GiocatoreException{};


class Giocatore : public QObject
{
    Q_OBJECT

private:
    int punti;
    QString nome;
    Collettore<Carta*> mano,mazzo;
public:
    explicit Giocatore(QString _nome="",int _punti=0,QObject* parent=0);
    virtual ~Giocatore();//per rendere classe polimorfa
    void addCarta(Carta*);
    void addCartaMano(Carta*);
    void pesca();//solleva eccezioni MazzoEsaurito
    const Collettore<Carta*>* getMano()const;
    Carta* estraiMano(const iterator_c &);
    Carta* estraiMano(unsigned int);//può sollevare eccezioni InvalidCarta
    void scarta(iterator_c&);
    void scarta(unsigned int);//può sollevare eccezioni InvalidCarta
    int getSizeMano()const;
    int getSizeMazzo()const;
    int getPunti()const;
    QString getNome()const;
    void increasePunti(int);
    void decreasePunti(int);
    virtual void agisci(Partita*);
public slots:
    void tira(unsigned int);
};

//#include "partita.h"

#endif // GIOCATORE_H
