#include "reader_window.h"
#include <QApplication>
#include "mainwin.h"
#include "books_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWin w;
    w.show();
    return a.exec();
}
