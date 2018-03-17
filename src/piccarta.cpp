#include "piccarta.h"
#include <iostream>
using namespace std;


const int PicCarta::w=170,PicCarta::h=255;
const double PicCarta::unita=1.19;

PicCarta::PicCarta(unsigned int _id,const QString& _nome,bool bianco) :
    QWidget(0),id(_id),l(this),nome(_nome,this),imm(0)
{
setGeometry(50,50,w,h);
setMaximumSize(w,h);
setMinimumSize(w,h);
l.setGeometry(0,0,width(),height());
l.setStyleSheet("background-color:rgb(255,0,0);");
l.setFrameShape(QFrame::Box);
nome.setGeometry(-20,10*unita,width(),20*unita);
nome.setFont(QFont("Helvetica",10*unita,QFont::Bold));
nome.setAlignment(Qt::AlignCenter);
if(bianco)nome.setStyleSheet("color:#ffffff;");
QString percorso=QString("Risorse/Immagini/")+_nome+QString(".jpg");
imm=new immCurva(this,percorso,150*unita,80*unita);
imm->setGeometry(10*unita,40*unita,width()-20*unita,80*unita);
}

void PicCarta::setBackground(const QPixmap &p,bool s){
    l.setPixmap(p);
    l.setScaledContents(s);
}

void PicCarta::mousePressEvent(QMouseEvent *){
    emit cliccata(id);
}


