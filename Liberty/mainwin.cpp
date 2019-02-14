#include "mainwin.h"
#include "ui_mainwin.h"
#include "reader_window.h"
#include "books_window.h"


MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    r = new reader_window();
    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(r, &reader_window::main_window, this, &MainWin::show);
    b = new books_window();
    //connect(b, &books_window::main_window, this, &MainWin::show);

}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::on_pushButton_clicked()
{
    r->show();

}


void MainWin::on_pushButton_2_clicked()
{
    b->show();
}
