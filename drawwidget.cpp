#include "drawwidget.h"
#include<QMouseEvent>
#include <QPainter>
#include <qfiledialog.h>
#include <qmessagebox.h>

DrawWidget::DrawWidget(){
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix=new QPixmap(size());
    pix->fill(Qt::white);
    ShapeDetecter shapedetecter;
    setMinimumSize(600,400);
}

DrawWidget::~DrawWidget(){
    delete pix;
    delete shapedetecter;
}

void DrawWidget::mousePressEvent(QMouseEvent *e)
{
    startPos=e->pos();
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPainter *painter=new QPainter;
    QPen pen;

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

void DrawWidget::save(){
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save File"),"",tr("PNG files(*.png)"));
    if(fileName!=""){
        if(!pix->save(fileName)){
            QMessageBox::critical(this,tr("error"),tr("Could not save file!"));
        };
    }
}

void DrawWidget::open(){
    QString fileName=QFileDialog::getOpenFileName(this,tr("Load File"),"",tr("PNG files(*.png)"));
    if(fileName!=""){
        if(!pix->load(fileName)){
            QMessageBox::critical(this,tr("error"),tr("Could not load file!"));
        };
    }
}

void DrawWidget::clear(){
    QPixmap *newPix=new QPixmap(size());
    newPix->fill(Qt::white);
    QPainter p(newPix);
    p.drawPixmap(QPoint(0,0),*newPix);
    pix=newPix;
    QWidget::update();
}

void DrawWidget::autoDetect(){
    QString currentPath=QDir::currentPath()+"/temp.png";
    if(!pix->save(currentPath)){
        QMessageBox::critical(this,tr("error"),tr("Could not save file!"));
    };
    QString fileName=QFileDialog::getSaveFileName(this,tr("output file"),"",tr("PNG files(*.png)"));
    if(fileName!=""){
        shapedetecter->shapeDetect(currentPath.toStdString(),fileName.toStdString());
    }
    if(!pix->load(fileName)){
        QMessageBox::critical(this,tr("error"),tr("Could not load file!"));
    };
}
