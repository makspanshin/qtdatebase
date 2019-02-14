#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "reader_window.h"
#include "books_window.h"
namespace Ui {
class MainWin;
}

class MainWin : public QDialog
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWin *ui;

    reader_window *r;
    books_window *b;
};



#endif // MAINWIN_H
