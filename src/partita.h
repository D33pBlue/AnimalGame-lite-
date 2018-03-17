#ifndef PARTITA_H
#define PARTITA_H

#include <QList>
#include <QWidget>
#include "giocatore.h"
#include "effetto.h"
#include "ai.h"
#include "campo.h"
#include <QObject>

//singleton
class Partita : public QObject
{
    Q_OBJECT

private:
    static Partita* ista_partita;
    unsigned int giro,turno,turniPerGiro;
    Giocatore *g;
    Giocatore *ai;
    bool toccaAI;
    Campo* campo;
    bool assegnaPunti();//true <=> il prossimo giro inizia il pc
    void pulisciCampo();
    explicit Partita(const QString& nomeGiocatore="",QObject*parent =0);
    Partita(const Partita&);//privato!
    void informaTiroAi(Carta*)const;
public:
    static Partita* getPartita();
    static Partita* createPartita(const QString&);
    static void deletePartita();
    virtual ~Partita();
    //assegnazione di default
    unsigned int getGiro()const;
    unsigned int getTurno()const;
    bool toccaPC()const;
    void avanzaTurno();
    bool terminata()const;
    bool vittoriaG1()const;
    void mettiInCampo(Carta*,Giocatore*);
    QString getNomeGiocatore()const;
    void assegnaCarte();
    Giocatore* getGiocatore()const;
    Giocatore* getAi()const;
    const Collettore<Campo::CartaGiocata>& getCampo()const;
    const Collettore<Carta*>* getMano()const;
    void togliDalCampo(Collettore<Campo::CartaGiocata>::iterator);
signals:
    void cambioStato();
    void mandaLog(QString);
    void finePartita();
};




#endif // PARTITA_H
