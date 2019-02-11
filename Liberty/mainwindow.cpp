#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reader_tabl.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
         * и инициализировать подключение к базе данных
         * */
    db = new reader_tabl();
    db->connectToDataBase();


    /* Инициализируем модель для представления данных
    * с заданием названий колонок
    * */
    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("ФИО")
                                   << trUtf8("ТЕЛ")
                     );

            /* Инициализируем внешний вид таблицы с данными
             * */
    this->createUI();
}
MainWindow::~MainWindow()
{
    delete ui;
}
/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
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

void MainWindow::createUI()
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

void MainWindow::on_add_user_clicked()
{
    if(ui->line_fio->text() == "" || ui->lineEdit_phone->text() == "")
    {
        QMessageBox::warning(this,"Добавление читателя",
                                  "Вы не заполнили поля");
    }
    else{
    Reader read;
    read.fio = ui->line_fio->text();
    read.phone = ui->lineEdit_phone->text();
    QVariantList data = db->add_reader(read.fio,read.phone);
    db->insertIntoTable(data);
    this->createUI();
    }
}

void MainWindow::on_Delete_reader_clicked()
{
    int a = ui->edit_delete_id->text().toInt();
    db->deleteFromTable(a);
    this->createUI();
}
