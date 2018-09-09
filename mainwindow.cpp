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

    setMinimumSize(600,400);

    showStyle();
    drawWidget->setWidth(widthSpinBox->value());
    drawWidget->setColor(Qt::black);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar=this->addToolBar("Tool");

    styleLabel=new QLabel(tr("line style"));
    styleComboBox=new QComboBox;

    styleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotDotLine));
    styleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox,SIGNAL(activated(int)),this,SLOT(showStyle()));

    widthLabel=new QLabel(tr("线宽:"));
    widthSpinBox=new QSpinBox;

    connect(widthSpinBox,SIGNAL(valueChanged(int)),drawWidget,SLOT(setWidth(int)));
    colorBtn=new QToolButton;
    QPixmap pixmap(20,20);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(showColor()));

    clearBtn=new QToolButton();
    clearBtn->setText(tr("清除"));
    connect(clearBtn,SIGNAL(clicked()),drawWidget,SLOT(clear()));

    toolBar->addWidget(styleLabel);
    toolBar->addWidget(styleComboBox);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpinBox);
    toolBar->addWidget(colorBtn);
    toolBar->addWidget(clearBtn);
}

void MainWindow::showStyle()
{
    drawWidget->setStyle(styleComboBox->itemData(styleComboBox->currentIndex(),Qt::UserRole).toInt());
}

void MainWindow::showColor()
{
    QColor color=QColorDialog::getColor(static_cast<int>(Qt::black),this);
    if(color.isValid()){
        drawWidget->setColor(color);
        QPixmap p(20,20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}
