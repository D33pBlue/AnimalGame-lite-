#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "animale.h"
#include "magia.h"
#include "arma.h"
#include "partita.h"
#include "piccarta.h"
#include <QVector>
#include "nuovapartita.h"
#include "esito.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void newGame(const QString&);

private slots:
    void tirataCarta(uint);
    void monitoraStato();
    void scriviLog(const QString&);
    void Finale();

    void on_actionNuova_Partita_triggered();

    void on_actionEsci_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    Partita *partita;
    QScrollArea *campo;
    QScrollArea * mano;
    QLabel *info,*messaggi;
    QVector<QString> logs;
    QLabel* logo;
    void resizeEvent(QResizeEvent*);
    void mostraPartita();
    void mostraMano();
    void mostraCampo();
    void mostraLogs();
    void cancellaPartita();
    QLabel* creaLogo()const;
};

#endif // MAINWINDOW_H
