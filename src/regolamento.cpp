#include "regolamento.h"
#include "ui_regolamento.h"

Regolamento::Regolamento(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regolamento)
{
    ui->setupUi(this);
    setWindowTitle("Regolamento AnimalGame");
    ui->textBrowser->setText(QString::fromUtf8("<p>Il gioco <strong>Animal</strong> è composto di 12 giri,"
    " divisi a loro volta in 4 turni.</p><p>Ad ogni turno un giocatore deve tirare in campo una carta."
    " La carta tirata mangerà automaticamente tutte le carte che può mangiare.</p><p>Per <strong>"
    "mangiare</strong> una carta in campo, la tua carta deve essere un animale con un tipo presente"
    " fra i nemici dell'altra, ed avere l'attacco maggiore o uguale alla resistenza di questa.</p>"
    "<p>Alla fine del giro le carte che mangiano qualcosa vengono tolte dal campo, e verranno assegnati"
   " dei punti ai giocatori nel modo seguente: 1 punto per ogni carta mangiata (+1 per la carta che mangia).</p>"
   "<p>Se la carta ha un effetto o è una carta magia allora l'effetto indicato si attiverà non appena la"
   " carta viene tirata.</p><p>Le carte arma invece possono mangiare indipendentemente dai nemici, ma non"
   " portano punti al giocatore.</p><p><strong>Per tirare una carta è sufficiente cliccarci sopra con il"
   " mouse, fuori dall'eventuale area di testo dove può essere spiegato un effetto.</strong></p>"
   "<p><strong>Le carte tirate dal computer vengono mostrate in una finestra che si chiude da sola dopo"
   " 3 secondi.</strong></p><p>Il primo a tirare in un giro sarà il giocatore che ha guadagnato più punti"
   " nel giro precedente, od eventualmente chi aveva iniziato prima in caso di parità.</p><p>"
   "<strong>Alla fine del 12° giro la partita termina e vince chi ha più punti in quel momento.</strong></p>"));
}

Regolamento::~Regolamento()
{
    delete ui;
}
