#include "books_tabl.h"
#include "connect_db.h"

books_tabl::books_tabl(QObject *parent) : QObject(parent)
{

}

books_tabl::~books_tabl()
{

}

bool books_tabl::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE "("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_TITLE      " VARCHAR(255)    NOT NULL,"
                            TABLE_WRITER     " VARCHAR(255)     NOT NULL"
                        ")"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

/* Метод для вставки записи в базу данных
 * */
bool books_tabl::insertIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_TITLE  ","
                                             TABLE_WRITER " ) "
                  "VALUES (:TITLE,:WRITER)");
    query.bindValue(":TITLE",     data[0].toString());
    query.bindValue(":WRITER",   data[1].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }

}

QVariantList books_tabl::add_books(QString title, QString writer)
{

    QVariantList data;
    data.append(title);
    data.append(writer);
    // Вставляем данные в БД
    return  data;
}

bool books_tabl :: deleteFromTable(int a)
{
     QSqlQuery query;

     query.prepare("DELETE FROM " TABLE " WHERE id=?" );

     query.addBindValue(a);

     if(!query.exec()){
         qDebug() << "error delete " << TABLE;
         qDebug() << query.lastError().text();
         return false;
     } else {
         return true;
     }
}
