#include "immcurva.h"

immCurva::immCurva(QWidget *parent,const QString& p,int _w,int _h) :
    QWidget(parent),image(QImage(p).scaled(_w,_h))
{}

void immCurva::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)

    QBrush brush(image);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(brush);
    painter.drawRoundedRect(0, 0, width(), height(), 20, 20);
}
