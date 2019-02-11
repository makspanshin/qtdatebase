#ifndef reader_tabl_H
#define reader_tabl_H

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

#define TABLE                   "Reader"
#define TABLE_FIO               "FIO"
#define TABLE_PHONE             "PHONE"

class Reader
{
public:
    QString fio;
    QString phone;
};

class reader_tabl : public QObject
{
    Q_OBJECT
public:
    explicit reader_tabl(QObject *parent = 0);

    ~reader_tabl();
    /* Методы для непосредственной работы с классом
     * Подключение к базе данных и вставка записей в таблицу
     * */
    void connectToDataBase();
    bool insertIntoTable(const QVariantList &data);
    bool deleteFromTable(int a);
    QVariantList add_reader(QString fio,QString phone) ;

private:
    // Сам объект базы данных, с которым будет производиться работа
    QSqlDatabase    db;

private:
    /* Внутренние методы для работы с базой данных
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTable();
};

#endif // reader_tabl_H
