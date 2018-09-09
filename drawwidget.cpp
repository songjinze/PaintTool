#include "drawwidget.h"
#include<QMouseEvent>
#include <QPainter>

DrawWidget::DrawWidget(){
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix=new QPixmap(size());
    pix->fill(Qt::white);
    setMinimumSize(600,400);
}

void DrawWidget::setStyle(int s)
{
    style=s;
}

void DrawWidget::setWidth(int w)
{
    weight=w;
}

void DrawWidget::setColor(QColor c)
{
    color=c;
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startPos=e->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter=new QPainter;
    QPen pen;
    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(pix);
    painter->setPen(pen);
    painter->drawLine(startPos,e->pos());
    painter->end();
    startPos=e->pos();

    this->update();

}

void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*pix);
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if(height()>pix->height()||width()>pix->width())
    {
        QPixmap *newPix=new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0,0),*pix);
        pix=newPix;
    }
    QWidget::resizeEvent(event);
}

void DrawWidget::clear(){
    QPixmap *newPix=new QPixmap(size());
    newPix->fill(Qt::white);
    QPainter p(newPix);
    p.drawPixmap(QPoint(0,0),*newPix);
    pix=newPix;
    QWidget::update();
}
