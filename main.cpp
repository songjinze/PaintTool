#include "notepad.h"

#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Notepad notepad;
    notepad.show();

    return a.exec();
}
