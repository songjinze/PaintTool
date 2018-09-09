#include <QMainWindow>

#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#endif // DRAWWIDGET_H

class DrawWidget:public QWidget
{
    Q_OBJECT
public:
    DrawWidget();
    void setStyle(int s);
    void setColor(QColor c);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent* event);
public slots:
    void setWidth(int w);
private slots:
    void clear();
private:
    QPixmap *pix;
    int style;
    int weight;
    QColor color;
    QPoint startPos;
};

