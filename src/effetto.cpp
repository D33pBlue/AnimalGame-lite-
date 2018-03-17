#include "effetto.h"
#include "e_mangiapesci.h"
#include "giocatore.h"
#include "e_scambia.h"
#include "e_spia.h"
#include "e_togli_avv.h"
#include "e_copia.h"

Effetto* traduciEffetto(QString cod,QString descri){
    if(cod==QString("E_mangiaPesci"))return new E_mangiaPesci(descri);
    if(cod==QString("E_scambia"))return new E_scambia(descri);
    if(cod==QString("E_copia"))return new E_copia(descri);
    if(cod==QString("E_spia"))return new E_spia(descri);
    if(cod==QString("E_togli_avv"))return new E_togli_avv(descri);
    return 0;
}


Effetto::Effetto(QString descri):descrizione(descri){}

Effetto::~Effetto(){}



QString Effetto::getDescrizione()const{
    return descrizione;
}


