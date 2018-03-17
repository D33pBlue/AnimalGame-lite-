#ifndef CAMPO_H
#define CAMPO_H

#include "collettore.h"
#include "carta.h"
#include "giocatore.h"


class Campo
{//Vuole essere un SINGLETON
public:
    class CartaGiocata{
    private:
        Carta* carta;
        Giocatore* giocatore;
        int carteMangiate;
    public:
        CartaGiocata(Carta*,Giocatore*,int);
        //~CartaGiocata(); standard => saranno altri metodi a deallocare le carte (e i giocatori)
        //c. copia standard
        //assegnazione standard
        bool operator==(const CartaGiocata&)const;
        bool operator!=(const CartaGiocata&)const;
        Carta* getCarta()const;
        Giocatore* getGiocatore()const;
        int getMangiate()const;
        void setGiocatore(Giocatore*);
        void setMangiate(int);
    };
private:
    static Campo* Istanza;
    Collettore<CartaGiocata> carte;

    Campo();
    Campo(const Campo&);
    Campo& operator=(const Campo&);
public:
    ~Campo();//dealloca le carte puntate nelle varie CartaGiocata, non i giocatori
    static Campo* getCampo();
    static void distruggiCampo();
    const Collettore<CartaGiocata>& getCarte()const;
    void addCarta(Carta*,Giocatore*,int);
    void removeCarta(Collettore<CartaGiocata>::iterator& it);
    //removeCarta dealloca anche la carta della CartaGiocata corrispondente
    CartaGiocata estrai(Collettore<CartaGiocata>::iterator &it);
};

#endif // CAMPO_H
