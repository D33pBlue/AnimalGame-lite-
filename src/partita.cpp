#include "partita.h"
#include <QDomDocument>
#include <QFile>
#include "animale.h"
#include "arma.h"
#include "animalece.h"
#include "magia.h"
#include "effetto.h"
#include <stdlib.h>
#include <time.h>
#include <QTimer>

Partita* Partita::ista_partita=0;

Partita::Partita(const QString &nomeGiocatore,QObject* parent):QObject(parent),giro(0),turno(0),turniPerGiro(4),g(new Giocatore(nomeGiocatore)),
    ai(new Ai()),toccaAI(0){
    campo=Campo::getCampo();
}


Partita::~Partita(){
    if(g)delete g;
    g=0;
    if(ai)delete ai;
    ai=0;
    Campo::distruggiCampo();
}

Partita* Partita::getPartita(){
    return ista_partita;
}

void Partita::deletePartita(){
    if(ista_partita)delete ista_partita;
    ista_partita=0;
}

Partita* Partita::createPartita(const QString &nome){
    if(!ista_partita)ista_partita=new Partita(nome);
    return ista_partita;
}



unsigned int Partita::getGiro()const{
    return giro;
}


unsigned int Partita::getTurno()const{
    return turno;
}

bool Partita::toccaPC()const{
    return toccaAI;
}

void Partita::avanzaTurno(){
    if(turno==turniPerGiro-1){
        toccaAI=assegnaPunti();
        pulisciCampo();
        giro++;
        turno=0;
        g->pesca();
        ai->pesca();
        emit(mandaLog(QString("Giro ")+QString::number(1+giro)));
    }
    else {
        turno++;
        toccaAI=(toccaAI+1)%2;
    }
    if(giro==12){
        emit finePartita();
    }
    else{
        emit cambioStato();

        if(toccaAI)ai->agisci(this);
        else g->agisci(this);
    }
}

bool Partita::terminata()const{
    return giro==12;
}

bool Partita::vittoriaG1()const{
    if(terminata())return g->getPunti()>=ai->getPunti();
    return false;
}

bool Partita::assegnaPunti(){
    const Collettore<Campo::CartaGiocata>& campo=Campo::getCampo()->getCarte();
    Collettore<Campo::CartaGiocata>::iterator it=campo.begin();
    int puntiG=0,puntiAi=0;
    while(it!=campo.end()){
        Campo::CartaGiocata carta=*it;
        int pti=carta.getMangiate();
        if(carta.getCarta()->getTipo()!=arma && pti>0){
            //le carte arma non portano punti
            if(carta.getGiocatore()==g)
                puntiG=puntiG+1+pti;
            else puntiAi=puntiAi+1+pti;
        }
        it++;
    }
    g->increasePunti(puntiG);
    ai->increasePunti(puntiAi);
    return puntiAi>puntiG || (puntiAi==puntiG && !toccaAI);
}

void Partita::pulisciCampo(){
    const Collettore<Campo::CartaGiocata>& camp=campo->getCarte();
    Collettore<Campo::CartaGiocata>::iterator it=camp.begin();
    while(it!=camp.end()){
        Campo::CartaGiocata carta=*it;
        if(carta.getMangiate()>0 || carta.getCarta()->getTipo()==arma ||
                carta.getCarta()->getTipo()==magia){
            campo->removeCarta(it);
        }
        else it++;
    }
}



Giocatore* Partita::getGiocatore()const{
    return g;
}

Giocatore* Partita::getAi()const{
    return ai;
}

void Partita::mettiInCampo(Carta *c, Giocatore *_g){
    if((toccaPC() && _g==ai) ||(!toccaPC() && _g==g)){
        QString inf=QString("[G")+QString::number(1+getGiro())+QString("T")+
                QString::number(1+getTurno())+QString("] ");
        if(_g==g)emit(mandaLog(inf+QString("Hai tirato: ")+c->getNome()));
        else emit(mandaLog(inf+QString("Ai tira: ")+c->getNome()));
        c->onTira(this,_g);
        int mangiate=0;
        Collettore<Campo::CartaGiocata>::iterator it=campo->getCarte().begin();
        while (it!=campo->getCarte().end()) {
            Carta* ccampo=(*it).getCarta();
            if(c->mangia(*ccampo)){
                mangiate+=1+(*it).getMangiate();
                emit(mandaLog(c->getNome()+QString(" mangia ")+ccampo->getNome()));
                campo->removeCarta(it);
            }
            else it++;
        }
        campo->addCarta(c,_g,mangiate);
        if(_g==ai)informaTiroAi(c);
        emit cambioStato();
        avanzaTurno();
    }
}

QString Partita::getNomeGiocatore()const{
    return g->getNome();
}

void Partita::assegnaCarte(){
    srand(time(0));
    QVector<Carta*> carte;
    //carico tutte le carte da file
    QDomDocument doc;
    QFile file("Risorse/Carte.xml");
    doc.setContent(&file);
    QDomNodeList xmlCarte=doc.elementsByTagName("carta");
    for(int i=0;i<xmlCarte.size();i++){
        QDomNode c=xmlCarte.item(i);
        int id=c.firstChildElement("id").text().toInt();
        QString nome=c.firstChildElement("nome").text();
        QString classe=c.firstChildElement("classe").text();
        if(classe==QString("animale")){
            Tipo tipo=traduciTipo(c.firstChildElement("tipo").text());
            int attacco=c.firstChildElement("attacco").text().toInt();
            int resistenza=c.firstChildElement("resistenza").text().toInt();
            Animale* anim=new Animale(id,nome,tipo,attacco,resistenza);
            QDomNodeList nemici=c.firstChildElement("nemici").elementsByTagName("n");
            for(int j=0;j<nemici.size();j++){
                QDomNode nem=nemici.item(j);
                anim->aggiungiNemico(traduciTipo(nem.toElement().text()));
            }
            carte.append(anim);
        }else if(classe==QString("animalece")){
            Tipo tipo=traduciTipo(c.firstChildElement("tipo").text());
            int attacco=c.firstChildElement("attacco").text().toInt();
            int resistenza=c.firstChildElement("resistenza").text().toInt();
            AnimaleCE* animCE=new AnimaleCE(id,nome,tipo,attacco,resistenza);
            QDomNodeList nemici=c.firstChildElement("nemici").elementsByTagName("n");
            for(int j=0;j<nemici.size();j++){
                QDomNode nem=nemici.item(j);
                animCE->aggiungiNemico(traduciTipo(nem.toElement().text()));
            }
            QString efCode=c.firstChildElement("effetto").text();
            QString descrizione=c.firstChildElement("descrizione").text();
            animCE->setEffetto(traduciEffetto(efCode,descrizione));
            carte.append(animCE);
        }else if(classe==QString("magia")){
            QString efCode=c.firstChildElement("effetto").text();
            QString descrizione=c.firstChildElement("descrizione").text();
            Magia* magi=new Magia(id,nome);
            magi->setEffetto(traduciEffetto(efCode,descrizione));
            carte.append(magi);
        }else if(classe==QString("arma")){
            int attacco=c.firstChildElement("attacco").text().toInt();
            carte.append(new Arma(id,nome,attacco));
        }
    }
    // assegno casualmente le carte ai giocatori

    const int GRANDEZZAMAZZO=40;
    while(g->getSizeMazzo()<GRANDEZZAMAZZO){
        int scelta=rand()%carte.size();
        g->addCarta(carte.at(scelta)->clona());
    }
    while(ai->getSizeMazzo()<GRANDEZZAMAZZO){
        int scelta=rand()%carte.size();
        ai->addCarta(carte.at(scelta)->clona());
    }
    for(int i=0;i<carte.size();++i)delete carte.at(i);
    carte.clear();
    g->pesca();
    ai->pesca();
}


const Collettore<Campo::CartaGiocata>& Partita::getCampo()const{
    return campo->getCarte();
}

const Collettore<Carta*>* Partita::getMano()const{
    return g->getMano();
}

void Partita::togliDalCampo(Collettore<Campo::CartaGiocata>::iterator it){
    campo->removeCarta(it);
}


void Partita::informaTiroAi(Carta* c)const{
    QDialog* info=new QDialog(0);
    QLabel* sfondo=new QLabel(info);
    sfondo->setGeometry(0,0,300,350);
    sfondo->setStyleSheet("background-color:#cd5c5c;");
    QVBoxLayout* lay=new QVBoxLayout(info);
    lay->setAlignment(Qt::AlignCenter);
    info->setLayout(lay);
    info->setWindowTitle("AnimalGame");
    QLabel *label=new QLabel("L'avversario tira:",info);
    label->setFont(QFont("Helvetica",13,QFont::Bold));
    lay->addWidget(label);
    lay->addWidget(c->getPicture());
    info->setGeometry(400,200,300,350);
    info->setMaximumSize(300,350);
    info->setMinimumSize(300,350);
    QTimer *timer=new QTimer(0);
    timer->singleShot(2000,info,SLOT(accept()));
    info->exec();
    delete info;
}


