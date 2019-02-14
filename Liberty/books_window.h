#ifndef BOOK_WINDOW_H
#define BOOK_WINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "books_tabl.h"

namespace Ui {
class books_window;
}

class books_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit books_window(QWidget *parent = nullptr);
    ~books_window();


private slots:
    void on_push_book_clicked();


    void on_push_delete_clicked();

protected:
    Ui::books_window *ui;
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
    books_tabl *db;
    QSqlTableModel  *model;

signals:
    void main_window();

};

#endif // BOOK_WINDOW_H
