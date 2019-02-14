#ifndef BOOKS_TABL_H
#define BOOKS_TABL_H


#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_HOSTNAME   "Liberty"
#define DATABASE_NAME       "Liberty.db"

#define TABLE                   "Books"
#define TABLE_TITLE             "title"
#define TABLE_WRITER            "writer"

class Book
{
  public:
    QString title_book;
    QString writer;
};

class books_tabl : public QObject
{
    Q_OBJECT
public:
    explicit books_tabl(QObject *parent = 0);

    ~books_tabl();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */

    bool insertIntoTable(const QVariantList &data);
    bool deleteFromTable(int a);
    QVariantList add_books(QString title,QString writer) ;

private:
    /* Внутренние методы для работы с базой данных
     * */

    bool createTable();
};

#endif // BOOKS_TABL_H
