#ifndef CARTA_H
#define CARTA_H

#include <QtCore>
#include <QtGui>

enum Tipo{NT=0,arma=1,carnivoro=2,uccello=3,insettivoro=5,
         pesce=7,rettile=11,onnivoro=13,erbivoro=17,insetto=19,
          pianta=23,magia=29};

Tipo traduciTipo(QString);

class Giocatore;
class Partita;

class Carta
{
private:
    unsigned int id;
    QString nome;
    Tipo tipo;
protected:
    QLabel* creaIconaTipo(QWidget*,Tipo,double)const;
public:
    Carta(unsigned int _id=0,const QString& _nome="",Tipo _tipo=NT);
    //costruttore di copia in versione standard
    virtual ~Carta();//virtuale in versione standard
    bool operator==(const Carta&)const;
    /*due carte sono considerate la stessa se hanno lo stesso id (gli altri campi possono essere
    diversi in quanto appartenenti a "istanze" diverse della stessa carta)*/
    bool operator!=(const Carta&)const;
    //Carta& operator=(const Carta&); versione standard
    unsigned int getId()const;
    QString getNome()const;//public?
    Tipo getTipo()const;
    virtual bool mangia(const Carta&)const=0;
    virtual void onTira(Partita*,Giocatore*)=0;
    virtual QWidget* getPicture()const=0;
    virtual Carta* clona()const=0;
};


#endif // CARTA_H
