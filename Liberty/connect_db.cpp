#include "connect_db.h"

#define TABLE "BOOKS"
void connect_db::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */
    if(!QFile("Liberty.db").exists()){
        //this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}

/* Методы восстановления базы данных
 * */
/*bool connect_db::restoreDataBase()
{
    if(this->openDataBase()){
        //if(!this->createTable()){
            //return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}
*/

/* Метод для открытия базы данных
 * */
bool connect_db::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("Liberty");
    db.setDatabaseName("Liberty.db");
    if(db.open()){
        return true;
    } else {
        return false;
    }
}


