#include "animalece.h"

AnimaleCE::AnimaleCE(unsigned int _id, const QString &_nome, Tipo _tipo,
                     unsigned int att, unsigned int res):
        Animale(_id,_nome,_tipo,att,res),effetto(0){}

AnimaleCE::AnimaleCE(const AnimaleCE & b): Animale(b),effetto(b.effetto->clona()){}


AnimaleCE::~AnimaleCE(){
    if(effetto){
        delete effetto;
    }
}

AnimaleCE& AnimaleCE::operator =(const AnimaleCE& a){
    if(*this!=a){
        Animale::operator=(a);
        effetto=a.effetto->clona();
    }
    return *this;
}

void AnimaleCE::setEffetto(Effetto *e){
    effetto=e;
}

void AnimaleCE::onTira(Partita*p,Giocatore*g){
    if(effetto)effetto->onTira(p,g);
}

PicCarta *AnimaleCE::getPicture()const{
    PicCarta* pic=new PicCarta(getId(),getNome());
    pic->setBackground(QPixmap("Risorse/Immagini/animalece.jpg"),true);

    QLabel*_tipo=creaIconaTipo(pic,getTipo(),pic->unita);
    _tipo->setGeometry(pic->w-30*pic->unita,5*pic->unita,20*pic->unita,20*pic->unita);

    QString info=QString("Res: ")+QString::number(getResistenza())+QString(" ~ Att: ")+
            QString::number(getAttacco());

    QLabel* inf=new QLabel(info,pic);//distruzione con pic
    inf->setFont(QFont("Helvetica",8*pic->unita,QFont::Bold));
    inf->setAlignment(Qt::AlignCenter);
    inf->setGeometry(0,115*pic->unita,pic->w,20*pic->unita);

    QWidget* nemBox=new QWidget(pic);
    //nemBox->setStyleSheet("background-color:#00994c;");
    QHBoxLayout* nem=new QHBoxLayout(nemBox);
    nemBox->setLayout(nem);
    nemBox->setGeometry(0,125*pic->unita,pic->w,40*pic->unita);
    if(haNemico(carnivoro))nem->addWidget(creaIconaTipo(pic,carnivoro,pic->unita));
    if(haNemico(uccello))nem->addWidget(creaIconaTipo(pic,uccello,pic->unita));
    if(haNemico(insettivoro))nem->addWidget(creaIconaTipo(pic,insettivoro,pic->unita));
    if(haNemico(pesce))nem->addWidget(creaIconaTipo(pic,pesce,pic->unita));
    if(haNemico(rettile))nem->addWidget(creaIconaTipo(pic,rettile,pic->unita));
    if(haNemico(onnivoro))nem->addWidget(creaIconaTipo(pic,onnivoro,pic->unita));
    if(haNemico(erbivoro))nem->addWidget(creaIconaTipo(pic,erbivoro,pic->unita));
    if(haNemico(insetto))nem->addWidget(creaIconaTipo(pic,insetto,pic->unita));
    if(haNemico(pianta))nem->addWidget(creaIconaTipo(pic,pianta,pic->unita));

    QTextBrowser *descri=new QTextBrowser(pic);
    descri->setPlainText(effetto->getDescrizione());
    descri->setGeometry(5,158*pic->unita,pic->w-10,pic->h-160*pic->unita-5);
    descri->setFrameShape(QFrame::NoFrame);
    descri->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    descri->setFont(QFont("serif",8));
    descri->setStyleSheet("background-image:url(Risorse/Immagini/bgtra.png); border-radius:10px;border-style:dashed;border-width:1px;border-color:rgb(0,153,56);");


    return pic;
}

Carta* AnimaleCE::clona()const{
    return new AnimaleCE(*this);
}
