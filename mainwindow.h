#include "drawwidget.h"

#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <qmainwindow.h>
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
private slots:
    void showStyle();
    void showColor();
private:
    DrawWidget *drawWidget;
    QLabel *widthLabel;
    QSpinBox *widthSpinBox;
    QLabel *styleLabel;
    QComboBox *styleComboBox;
    QToolButton *colorBtn;
    QToolButton *clearBtn;
};
