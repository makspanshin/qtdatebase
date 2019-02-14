#ifndef reader_window_H
#define reader_window_H
#include <QMainWindow>
#include <QSqlTableModel>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
#include "reader_tabl.h"

namespace Ui {
class reader_window;
}

class reader_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit reader_window(QWidget *parent = nullptr);
    ~reader_window();

private slots:
    void on_add_user_clicked();

    void on_Delete_reader_clicked();

protected:
    Ui::reader_window *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    reader_tabl       *db;
    QSqlTableModel  *model;
private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();

signals:
    void main_window();  // Сигнал для первого окна на открытие
};

#endif // reader_window_H
