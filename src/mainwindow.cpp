#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regolamento.h"


#include <iostream>
using namespace std;

typedef Collettore<Carta*>::iterator mazzo_it;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),partita(0),campo(0),mano(0),info(0),messaggi(0),logo(0)
{
    setMinimumSize(1024,640);
    ui->setupUi(this);
    logo=creaLogo();
    setWindowTitle("AnimalGame");
}

QLabel* MainWindow::creaLogo()const{
    QLabel *l=new QLabel(ui->centralWidget);
    l->setPixmap(QPixmap("Risorse/Immagini/AnimalLogo.png"));
    l->setScaledContents(true);
    l->setGeometry((width()-181)/2,(height()-203)/2,181,203);
    l->setVisible(true);
    return l;
}

void MainWindow::cancellaPartita(){
    Partita* p=partita;
    partita=0;
    if(messaggi){delete messaggi;messaggi=0;}
    if(info){delete info;info=0;}
    if(mano){delete mano;mano=0;}
    if(campo){delete campo;campo=0;}
    if(p)p->deletePartita();
    logs.clear();
}

void MainWindow::newGame(const QString & gioc){
    cancellaPartita();
    partita=Partita::createPartita(gioc);
    QObject::connect(partita,SIGNAL(cambioStato()),this,SLOT(monitoraStato()));
    QObject::connect(partita,SIGNAL(mandaLog(QString)),this,SLOT(scriviLog(QString)));
    QObject::connect(partita,SIGNAL(finePartita()),this,SLOT(Finale()));
    partita->assegnaCarte();
    if(logo){delete logo;logo=0;}
    mostraPartita();
}

MainWindow::~MainWindow()
{
    if(logo)delete logo;
    if(messaggi)delete messaggi;
    if(info)delete info;
    if(mano)delete mano;
    if(campo)delete campo;
    if(partita)delete partita;
    delete ui;
}

void MainWindow::mostraMano(){
    mano=new QScrollArea(ui->centralWidget);
    mano->setGeometry(150,height()/2,width()-150,height()/2);
    mano->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mano->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mano->setVisible(true);
    mano->setFrameShape(QFrame::NoFrame);
    QWidget *boxMano=new QWidget(mano);
    mano->setWidget(boxMano);
    QHBoxLayout *layMano=new QHBoxLayout(boxMano);
    layMano->setMargin(0);
    boxMano->setLayout(layMano);
    int wscr=(width()-155> 870)? width()-150 :870;
    boxMano->setGeometry(0,0,wscr,305);
    const Collettore<Carta*>* carteMano=partita->getMano();
    for(Collettore<Carta*>::iterator it=carteMano->begin();it!=carteMano->end();it++){
        Carta* c=*it;
        QWidget* p=c->getPicture();
        p->setParent(boxMano);
        layMano->addWidget(p);
        PicCarta *pic=dynamic_cast<PicCarta*>(p);
        if(pic){
            QObject::connect(pic,SIGNAL(cliccata(uint)),partita->getGiocatore(),SLOT(tira(uint)));
            QObject::connect(pic,SIGNAL(cliccata(uint)),this,SLOT(tirataCarta(uint)));
        }
    }
}

void MainWindow::mostraCampo(){
    campo=new QScrollArea(ui->centralWidget);
    campo->setVisible(true);
    campo->setGeometry(0,20,width(),height()/2);
    campo->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    campo->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    campo->setFrameShape(QFrame::NoFrame);
    QWidget* boxCampo=new QWidget(campo);
    campo->setWidget(boxCampo);
    QVBoxLayout *layCampo=new QVBoxLayout(boxCampo);
    boxCampo->setLayout(layCampo);
    const Collettore<Campo::CartaGiocata>& carteCampo=partita->getCampo();
    int limLinea=width()/180,linee=1,lin=0;
    QWidget* linea=new QWidget(boxCampo);
    layCampo->addWidget(linea);
    QHBoxLayout* layLinea=new QHBoxLayout(linea);
    linea->setLayout(layLinea);
    for(Collettore<Campo::CartaGiocata>::iterator it=carteCampo.begin();it!=carteCampo.end();it++){
        Campo::CartaGiocata c=*it;
        QWidget* cgioc=new QWidget(linea);
        cgioc->setMaximumSize(170,280);
        cgioc->setMinimumSize(170,280);
        QWidget* p=c.getCarta()->getPicture();
        p->setParent(cgioc);
        p->setGeometry(0,0,170,255);
        QLabel* mang=new QLabel(cgioc);
        QString val=QString("#mang: ")+QString::number(c.getMangiate());
        if(c.getGiocatore()->getNome()==partita->getAi()->getNome()){
            val+=QString(" [di Ai]");
            mang->setStyleSheet("color:#f50000;");
        }
        mang->setText(val);
        mang->setAlignment(Qt::AlignCenter);
        mang->setGeometry(0,250,170,25);
        mang->setFont(QFont("Helvetica",12));
        mang->setVisible(true);
        layLinea->addWidget(cgioc);
        lin++;
        if(lin==limLinea){
            lin=0;
            linee++;
            linea=new QWidget(boxCampo);
            layCampo->addWidget(linea);
            layLinea=new QHBoxLayout(linea);
            linea->setLayout(layLinea);
        }
    }
    int altezza=320*(linee-1);
    if(lin>0)altezza+=320;
    boxCampo->setGeometry(0,0,width(),altezza);
}

void MainWindow::mostraPartita(){
    if(partita){
        if(campo){delete campo;campo=0;}
        if(mano){delete mano;mano=0;}
        if(info){delete info;}
        QString inf=QString("Giro: ")+QString::number(1+partita->getGiro())+
                QString("/12  ~  Turno: ")+QString::number(1+partita->getTurno())+QString("/4")+
                QString("  ~  Punti Ai: ")+QString::number(partita->getAi()->getPunti())+
                QString("  ~  Punti ")+partita->getGiocatore()->getNome()+QString(": ")+
                QString::number(partita->getGiocatore()->getPunti());
        info=new QLabel(inf,ui->centralWidget);
        info->setVisible(true);
        info->setGeometry(10,0,700,18);
        info->setFont(QFont("Helvetica",12));
        mostraMano();
        mostraCampo();
        mostraLogs();
    }
}


void MainWindow::tirataCarta(uint){
    mostraPartita();
}

void MainWindow::resizeEvent(QResizeEvent *){
    mostraPartita();
    if(logo)logo->setGeometry((width()-181)/2,(height()-203)/2,181,203);
}

void MainWindow::monitoraStato(){
    mostraPartita();
}

void MainWindow::scriviLog(const QString &s){
    logs.append(s);
}

void MainWindow::mostraLogs(){
    if(messaggi)delete messaggi;
    messaggi=new QLabel(ui->centralWidget);
    messaggi->setStyleSheet("background-color:#00f888;");
    QVBoxLayout* laymex=new QVBoxLayout(messaggi);
    messaggi->setGeometry(0,height()/2+25,148,255);
    messaggi->setVisible(true);
    int i=logs.size()-8;
    if(i<0)i=0;
    for(;i<logs.size();i++){
        QLabel *mex=new QLabel(logs.at(i),messaggi);
        mex->setFont(QFont("Helvetica",8));
        mex->setMaximumHeight(20);
        laymex->addWidget(mex);
    }
}

void MainWindow::on_actionNuova_Partita_triggered()
{
    NuovaPartita* nuova=new NuovaPartita(this);
    QObject::connect(nuova,SIGNAL(nuova(QString)),this,SLOT(newGame(QString)));
    nuova->show();
}

void MainWindow::on_actionEsci_triggered()
{
    qApp->quit();
}

void MainWindow::Finale(){
    Esito* esito=new Esito(this,partita->getAi()->getPunti(),partita->getGiocatore()->getPunti());
    esito->show();
    cancellaPartita();
    logo=creaLogo();
}

void MainWindow::on_actionAbout_triggered()
{
    Regolamento* reg=new Regolamento(this);
    reg->exec();
    delete reg;
}
