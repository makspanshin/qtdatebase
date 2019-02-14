#ifndef CONNECT_DB_H
#define CONNECT_DB_H
#define TABLE_TITLE             "title"
#define TABLE_WRITER            "writer"
#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

class connect_db
{
private:
    static connect_db * p_instance;
    // Конструкторы и оператор присваивания недоступны клиентам
    connect_db() {
        connectToDataBase();
    }
    connect_db( const connect_db& );
    connect_db& operator=( connect_db& );
    void connectToDataBase();
    bool openDataBase();
    bool restoreDataBase();
  public:
    QSqlDatabase  db;
    static connect_db& getInstance() {
        static connect_db  instance;
        return instance;
    }
};


#endif // CONNECT_DB_H
