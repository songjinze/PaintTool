#include "mainwindow.h"
#include <QToolButton>
#include<QtGui>
#include<QToolBar>
#include <QColorDialog>
MainWindow::MainWindow()
{

    drawWidget=new DrawWidget;
    this->setCentralWidget(drawWidget);

    createToolBar();
    this->addToolBar(toolBar);
    setMinimumSize(600,400);
}

void MainWindow::createToolBar()
{

    QPixmap pixmap(20,20);
    pixmap.fill(Qt::black);
    toolBar=new QToolBar;
    newShapeBtn=new QToolButton;
    newShapeBtn->setText(tr("new Shape"));
    saveBtn=new QToolButton;
    saveBtn->setText(tr("save"));
    loadBtn=new QToolButton;
    loadBtn->setText(tr("load"));
    clearBtn=new QToolButton;
    clearBtn->setText(tr("clear"));
    connect(newShapeBtn,SIGNAL(clicked()),drawWidget,SLOT());
    connect(saveBtn,SIGNAL(clicked()),drawWidget,SLOT(save()));
    connect(loadBtn,SIGNAL(clicked()),drawWidget,SLOT(open()));
    connect(clearBtn,SIGNAL(clicked()),drawWidget,SLOT(clear()));

    toolBar->addWidget(saveBtn);
    toolBar->addWidget(loadBtn);
    toolBar->addWidget(clearBtn);
}

