#include "plotter.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <vector>


Plotter::Plotter(QWidget *parent) : QWidget(parent){

}

void Plotter::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QBrush brush;
    QPen pen;

    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);

    pen.setColor(Qt::red);
    pen.setWidth(2);

    painter.setBrush(brush);
    painter.setPen(pen);
    painter.drawRect(0,0,width(),height());

}
