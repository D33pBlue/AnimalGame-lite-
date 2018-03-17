#ifndef PICCARTA_H
#define PICCARTA_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include "carta.h"
#include "immcurva.h"

class PicCarta : public QWidget
{
    Q_OBJECT
private:
    void mousePressEvent(QMouseEvent *);
    unsigned int id;
    QLabel l,nome;
    immCurva *imm;
public:
    explicit PicCarta(unsigned int _id,const QString&,bool =false);
    static const int w,h;
    static const double unita;
    void setBackground(const QPixmap&,bool scaled=false);
signals:
    void cliccata(unsigned int);
};

#endif // PICCARTA_H
