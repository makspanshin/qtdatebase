#include "books_window.h"
#include "ui_books_window.h"

#include "books_window.h"
#include "ui_books_window.h"
#include "connect_db.h"
#include <QMessageBox>
#include "books_tabl.h"

books_window::books_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::books_window)
{
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
        * и инициализировать подключение к базе данных
         * */
   auto& db = connect_db::getInstance();

    /* Инициализируем модель для представления данных
    * с заданием названий колонок
    * */
    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Название")
                                   << trUtf8("Писатель")
                     );

            /* Инициализируем внешний вид таблицы с данными
             * */
    this->createUI();
}



books_window::~books_window()
{
    delete ui;
}


void books_window::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void books_window::createUI()
{
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    ui->tableView->setColumnHidden(0, false);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы
}





void books_window::on_push_book_clicked()
{

    if(ui->line_title->text() == "" || ui->line_writer->text() == "")
    {
        QMessageBox::warning(this,"Добавление книги",
                                  "Вы не заполнили поля");
    }
    else{
    Book book;
    book.title_book = ui->line_title->text();
    book.writer = ui->line_writer->text();
    QVariantList data = db->add_books(book.title_book, book.writer);
    db->insertIntoTable(data);
    this->createUI();
    }
}

void books_window::on_push_delete_clicked()
{
    int a = ui->line_delete ->text().toInt();
    db->deleteFromTable(a);
    this->createUI();
}
