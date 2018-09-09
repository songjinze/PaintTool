
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <qmainwindow.h>

#ifndef NOTEPAD_H
#define NOTEPAD_H

#endif // NOTEPAD_H

class Notepad: public QMainWindow
{
    Q_OBJECT

public:
    Notepad();

private slots:
    void open();
    void save();
    void quit();

private:

    QTextEdit *textEdit;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};
