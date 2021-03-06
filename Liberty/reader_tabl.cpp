#include "reader_tabl.h"
#include "connect_db.h"

reader_tabl::reader_tabl(QObject *parent) : QObject(parent)
{

}

reader_tabl::~reader_tabl()
{

}


/* Метод для создания таблицы в базе данных
 * */
bool reader_tabl::createTable()
{
    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " TABLE "("
                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                            TABLE_FIO       " VARCHAR(255)    NOT NULL,"
                            TABLE_PHONE     " VARCHAR(12)     NOT NULL"
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
bool reader_tabl::insertIntoTable(const QVariantList &data)
{
    /* Запрос SQL формируется из QVariantList,
     * в который передаются данные для вставки в таблицу.
     * */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
     * которые потом связываются методом bindValue
     * для подстановки данных из QVariantList
     * */
    query.prepare("INSERT INTO " TABLE " ( " TABLE_FIO ","
                                             TABLE_PHONE " ) "
                  "VALUES (:FIO,:PHONE)");
    query.bindValue(":FIO",     data[0].toString());
    query.bindValue(":PHONE",   data[1].toString());
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }

}
QVariantList reader_tabl::add_reader(QString fio, QString phone)
{

    QVariantList data;
    data.append(fio);
    data.append(phone);
    // Вставляем данные в БД
    return  data;
}
bool reader_tabl :: deleteFromTable(int a)
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
