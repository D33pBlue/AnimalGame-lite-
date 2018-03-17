#ifndef COLLETTORE_H
#define COLLETTORE_H

#include <iostream>
using namespace std;

class CollettoreException{};
class RemoveFromEmpty:public CollettoreException{};
class RemoveEndIterator:public CollettoreException{};

template <class T>
class Collettore
/*Template di lista bilinkata con apparente MEMORIA CONDIVISA, ma senza la possibilità di costruire duplicati
(ogni istanza è unica modulo riferimenti). Con inserimento in coda o prima di iteratore.*/
{
private:
    class Nodo{
      public:
        T info;
        Nodo *next,*prec;
        Nodo();
        Nodo(const T&,Nodo* =0,Nodo* =0);
        //~Nodo(); in versione standard
    };

    Nodo *testa,*coda;
    int length;
    //iterator pte;

    Collettore(const Collettore&);//privato per non fare duplicazioni!
    Collettore& operator=(const Collettore&);//privato per evitare duplicazioni

public:
    class iterator{
    /*friend void Collettore::insert(const T &, const iterator &);
    friend iterator Collettore::find(const T &) const;
    friend iterator Collettore::begin()const;
    friend iterator Collettore::end()const;*/
    friend class Collettore;
    private:
        Nodo* pos;
        iterator(Nodo* =0);
    public:
        iterator& operator++();
        iterator operator ++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator ==(const iterator&)const;
        bool operator !=(const iterator&)const;
        bool hasNext()const;
        bool hasPrec()const;
        T& operator*()const;
    };

    Collettore();
    ~Collettore();
    bool operator==(const Collettore&)const;
    bool operator!=(const Collettore&)const;
    void insert(const T&);//aggiunge in coda
    void insert(const T&,const iterator&);//aggiunge nella posizione che precede l'iteratore
    iterator& remove(iterator&);//elimina elemento puntato e punta a elemento successivo
    void remove(const T&);//può sollevare eccezioni CollettoreException
    T estrai(const iterator&);//può sollevare eccezioni CollettoreException
    iterator find(const T&)const;
    //ritorna l'iteratore che punta ad una occorrenza di un nodo con info cercata
    void clear();
    int size()const;
    bool empty()const;
    iterator begin()const;
    iterator fine()const;
    iterator end()const;
};

// DEFINIZIONI METODI Collettore<T>::Nodo

template <class T>
Collettore<T>::Nodo::Nodo():next(0),prec(0){}

template <class T>
Collettore<T>::Nodo::Nodo(const T & i, Nodo *n,Nodo* p):info(i),next(n),prec(p){}


//DEFINIZIONI METODI Collettore<T>::iterator

template<class T>
Collettore<T>::iterator::iterator(Nodo *n):pos(n){}

template<class T>
typename Collettore<T>::iterator& Collettore<T>::iterator::operator++(){
    if(pos)pos=pos->next;
    return *this;
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::iterator::operator++(int){
    iterator k=(*this);
     if(pos)pos=pos->next;
     return k;
}

template<class T>
typename Collettore<T>::iterator& Collettore<T>::iterator::operator--(){
    if(pos)pos=pos->prec;
    return *this;
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::iterator::operator--(int){
    iterator k=(*this);
     if(pos)pos=pos->prec;
     return k;
}

template<class T>
bool Collettore<T>::iterator::operator==(const iterator& i)const{
    return pos==i.pos;
}

template<class T>
bool Collettore<T>::iterator::operator!=(const iterator& i)const{
    return pos!=i.pos;
}

template<class T>
bool Collettore<T>::iterator::hasNext()const{
    return (pos->next)!=0;
}

template<class T>
bool Collettore<T>::iterator::hasPrec()const{
    return (pos->prec)!=0;
}

template<class T>
T& Collettore<T>::iterator::operator*()const{
    return pos->info;
}

//DEFINIZIONI METODI Collettore<T>

template <class T>
Collettore<T>::Collettore():testa(0),coda(0),length(0){}

template <class T>
Collettore<T>::~Collettore(){
    clear();
}

template <class T>
bool Collettore<T>::operator ==(const Collettore& c)const{
    return length==c.length && testa==c.testa && coda==c.coda;
}

template <class T>
bool Collettore<T>::operator !=(const Collettore& c)const{
    return length!=c.length || testa!=c.testa || coda!=c.coda;
}

template <class T>
void Collettore<T>::insert(const T & t){
    if(!coda){
        coda=new Nodo(t);
        testa=coda;
    }
    else{
        coda->next=new Nodo(t,0,coda);
        coda=coda->next;
    }
    length++;
}

template <class T>
void Collettore<T>::insert(const T &t, const iterator &it){
    if(it==end())insert(t);
    else{
       // essendo (it != past-the-end) allora esiste almeno un nodo
        it.pos->prec=new Nodo(t,it.pos,it.pos->prec);
        if(testa->prec)testa=testa->prec;
        else it.pos->prec->prec->next=it.pos->prec;
        length++;
    }
}

template <class T>
typename Collettore<T>::iterator& Collettore<T>::remove(iterator &it){
    if(length==0)throw RemoveFromEmpty();
    if(it==end())throw RemoveEndIterator();
    Nodo *n=it.pos;
    if(!n->prec){
              testa=n->next;
            if(testa)testa->prec=0;
            else coda=testa;
        }
    else{
            //n->prec definito
            n->prec->next=n->next;
            if(n->next)n->next->prec=n->prec;
            else coda=n->prec;
        }
    Nodo* r=(n)? n->next : 0;
    delete n;
    length--;
    it.pos=r;
    return it;
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::find(const T &t) const{
    iterator k;
    Nodo *i=testa,*j=coda;
    while(!k.pos && i && j && i->prec!=j){
        if(i->info==t)k.pos=i;
        if(j->info==t)k.pos=j;
        i=i->next;
        j=j->prec;
    }
    if(!k.pos)return end();
    return k;
}

template<class T>
void Collettore<T>::remove(const T &t){
    if(length==0)throw RemoveFromEmpty();
    iterator k=find(t);
    if(k==end())throw RemoveEndIterator();
    remove(k);
}


template<class T>
T Collettore<T>::estrai(const iterator &it){
    T x=(*it);
    remove(const_cast<iterator&>(it));
    return x;
}

template<class T>
void Collettore<T>::clear(){
    while (testa) {
        Nodo* k=testa;
        testa=testa->next;
        delete k;
        length--;
    }
    coda=0;
}

template<class T>
int Collettore<T>::size()const{
    return length;
}


template<class T>
bool Collettore<T>::empty()const{
    return length==0;
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::begin() const{
    return iterator(testa);
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::end() const{
    return iterator(0);
}

template<class T>
typename Collettore<T>::iterator Collettore<T>::fine() const{
    return iterator(coda);
}

#endif // COLLETTORE_H
