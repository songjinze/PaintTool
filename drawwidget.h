#include <QMainWindow>
#include "shapedetecter.h"
#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#endif // DRAWWIDGET_H

class DrawWidget:public QWidget
{
    Q_OBJECT
public:
    DrawWidget();
    ~DrawWidget();
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent* event);
private slots:
    void save();
    void open();
    void clear();
private:
    QPixmap *pix;
    QPoint startPos;
    ShapeDetecter *shapedetecter;
};

