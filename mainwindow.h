#include "drawwidget.h"
#include <qtoolbar.h>
#include <qtoolbutton.h>
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#endif // MAINWINDOW_H

class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private:
    void createToolBar();
    void initBar();
private:
    DrawWidget *drawWidget;
    QToolButton *newShapeBtn;
    QToolButton *saveBtn;
    QToolButton *loadBtn;
    QToolButton *clearBtn;
    QToolBar *toolBar;
};
