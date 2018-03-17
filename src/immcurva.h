#ifndef IMMCURVA_H
#define IMMCURVA_H

#include <QWidget>
#include <QtGui>

class immCurva : public QWidget
{
    Q_OBJECT
public:
    explicit immCurva(QWidget *parent = 0,const QString& ="",int _w=0,int _h=0);
private:
    void paintEvent(QPaintEvent *);
    QImage image;
signals:

public slots:

};

#endif // IMMCURVA_H
