#include "mainwindow.h"
#include <QApplication>
#include "errorecaricamento.h"
#include <fstream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::ifstream inp("Risorse/Carte.xml");
    if(!inp){
        ErroreCaricamento *err=new ErroreCaricamento();
        return err->exec();
    }
    inp.close();

    a.setWindowIcon(QIcon(QPixmap("Risorse/Immagini/icona.jpg")));

    MainWindow w;
    w.show();

    return a.exec();
}
