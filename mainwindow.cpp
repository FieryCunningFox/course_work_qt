#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, int m_artikul, shop_list* m_shops, shop* m_current_shop, bool m_isModificate, QString m_current_file)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), shops(m_shops), current_shop_artikul(m_artikul), current_shop(m_current_shop), isModicate(m_isModificate), current_file(m_current_file)
{
    ui->setupUi(this);

    setWindowTitle(tr("%1[*]").arg("Information about electronic shop"));

    shops = new shop_list(); // список всех магазинов
    current_shop = new shop(); // текущий магазин
    shops->add_node(current_shop); // добавление текущего магазина в спсок магазинов сети

    // установка заголовков, количества столбцов по таблицам, отображающим данные
    ui->table_notebooks_3->setColumnCount(8); // таблица ноутбуков
    ui->table_notebooks_3->setRowCount(0);
    QStringList Title_notebook;
    Title_notebook << "ID"
                  << "Artikul"
                  << "Number"
                  << "Cost"
                  << "Firma"
                  << "Memory size"
                  << "Rasrad"
                  << "Architecture";
    ui->table_notebooks_3->setHorizontalHeaderLabels(Title_notebook);
    ui->table_notebooks_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_notebooks_3->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_notebooks_3->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_notebooks_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->table_smartphones_3->setColumnCount(8); // таблица смартфонов
    ui->table_smartphones_3->setRowCount(0);
    QStringList Title_smartphone;
    Title_smartphone << "ID"
                     << "Artikul"
                     << "Number"
                     << "Cost"
                     << "Firma"
                     << "Screen size"
                     << "Hours working"
                     << "Year production";
    ui->table_smartphones_3->setHorizontalHeaderLabels(Title_smartphone);
    ui->table_smartphones_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_smartphones_3->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_smartphones_3->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_smartphones_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->table_tvs_3->setColumnCount(8); // таблица телевизоров
    ui->table_tvs_3->setRowCount(0);
    QStringList Title_tv;
    Title_tv << "ID"
             << "Artikul"
             << "Number"
             << "Cost"
             << "Firma"
             << "Screen size"
             << "Internet connect"
             << "Number channels";
    ui->table_tvs_3->setHorizontalHeaderLabels(Title_tv);
    ui->table_tvs_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_tvs_3->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_tvs_3->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_tvs_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->search_table->setColumnCount(8); // таблица с результатами поиска
    ui->search_table->setRowCount(0);
    ui->search_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->search_table->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->table_shops->setColumnCount(4); // таблица магазинов
    ui->table_shops->setRowCount(current_shop->get_number_shop());
    QStringList Title_shops;
    Title_shops << "ID"
                << "Name"
                << "Adress"
                << "Phone";
    ui->table_shops->setHorizontalHeaderLabels(Title_shops);
    ui->table_shops->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_shops->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_shops->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_shops->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // установка валидаторов для защиты от некорректных данных
    QRegExp num("[0-9]{1,11}");
    QValidator *numValidator = new QRegExpValidator(num, this);
    ui->artikul_notebook->setValidator(numValidator);
    ui->artikul_smartphone->setValidator(numValidator);
    ui->artikul_tv->setValidator(numValidator);
    ui->cost_notebook->setValidator(numValidator);
    ui->cost_smartphone->setValidator(numValidator);
    ui->cost_tv->setValidator(numValidator);
    ui->screen_size->setValidator(numValidator);
    ui->memory->setValidator(numValidator);
    ui->screen_size->setValidator(numValidator);
    ui->screen_size_sm->setValidator(numValidator);
    ui->hours_working->setValidator(numValidator);
    ui->number_chanels->setValidator(numValidator);
    ui->phone_shop->setValidator(numValidator);

    QRegExp year("[0-9]{1,4}");
    QValidator *yearValidator = new QRegExpValidator(year, this);
    ui->year_production->setValidator(yearValidator);

    // отображение текущего количества продуктов и магазинов
    ui->count_notebooks->setText(QString::number(current_shop->get_ware()->get_count_notebooks()));
    ui->count_smartphones->setText(QString::number(current_shop->get_ware()->get_count_smartphones()));
    ui->count_tvs->setText(QString::number(current_shop->get_ware()->get_count_tvs()));
    ui->all_products->setText(QString::number(current_shop->get_ware()->get_count()));
    ui->number_shops->setText(QString::number(shops->get_count_all_shops()));

   //  файловое меню - добавление действий
    ui->menuFile->addAction("Create new", this, SLOT(new_file()));
    ui->menuFile->addAction("Open file", this, SLOT(open_file()));
    ui->menuFile->addAction("Save", this, SLOT(save_file()));
    ui->menuFile->addAction("Save as", this, SLOT(save_as()));
    ui->menuFile->addAction("Exit", this, SLOT(exit_prog()));

    ui->menuDescribe->addAction("How use this program...", this, SLOT(help()));
    ui->menuDescribe->addAction("About program", this, SLOT(about_program()));

    ui->menu->setCurrentIndex(0); // главное меню выбора действий
    ui->tables->setCurrentIndex(0); // отображение таблицы с продуктами

    ui->products->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_table() { // обновление таблицы продуктов
    int number_notebooks = current_shop->get_ware()->get_count_notebooks();
    int number_smartphones = current_shop->get_ware()->get_count_smartphones();
    int number_tvs = current_shop->get_ware()->get_count_tvs();

    // установка нового количества строк в таблицах
    ui->table_notebooks_3->setRowCount(number_notebooks);
    ui->table_smartphones_3->setRowCount(number_smartphones);
    ui->table_tvs_3->setRowCount(number_tvs);

    // отображение текущего количества продуктов и магазинов
    ui->count_notebooks->setText(QString::number(current_shop->get_ware()->get_count_notebooks()));
    ui->count_smartphones->setText(QString::number(current_shop->get_ware()->get_count_smartphones()));
    ui->count_tvs->setText(QString::number(current_shop->get_ware()->get_count_tvs()));
    ui->all_products->setText(QString::number(current_shop->get_ware()->get_count()));

    product* current = current_shop->ware->get_head();
    int i1 = 0, i2 = 0, i3 = 0; // счетчики для заполнения таблиц
    while (current != nullptr){
        QTableWidgetItem *item;

        if (current->get_category() == "Notebook") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_notebooks_3->setItem(i1, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_notebooks_3->setItem(i1, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_notebooks_3->setItem(i1, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_notebooks_3->setItem(i1, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_notebooks_3->setItem(i1, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_notebooks_3->setItem(i1, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_notebooks_3->setItem(i1, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_notebooks_3->setItem(i1, 7, item);
            i1++;
        }

        if (current->get_category() == "Smartphone") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_smartphones_3->setItem(i2, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_smartphones_3->setItem(i2, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_smartphones_3->setItem(i2, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_smartphones_3->setItem(i2, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_smartphones_3->setItem(i2, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_smartphones_3->setItem(i2, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_smartphones_3->setItem(i2, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_smartphones_3->setItem(i2, 7, item);
            i2++;
        }

        if (current->get_category() == "TV") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_tvs_3->setItem(i3, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_tvs_3->setItem(i3, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_tvs_3->setItem(i3, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_tvs_3->setItem(i3, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_tvs_3->setItem(i3, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_tvs_3->setItem(i3, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_tvs_3->setItem(i3, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_tvs_3->setItem(i3, 7, item);
            i3++;
        }

        current = current->get_next();
    }

    // снятие фокуса строк с таблиц
    ui->table_notebooks_3->clearSelection();
    ui->table_smartphones_3->clearSelection();
    ui->table_tvs_3->clearSelection();
}

void MainWindow::update_table_shops() { // обновление таблицы магазинов
    ui->number_shops->setText(QString::number(shops->get_count_all_shops())); // отображение количества магазинов
    ui->table_shops->setRowCount(shops->get_count_all_shops()); // установка нового количества строк

    shop* current = shops->get_head();
    int i = 0; // счетчик для заполнения таблицы
    while (current != nullptr) {
        QTableWidgetItem *item;
        item = new QTableWidgetItem(QString::number(current->get_artikul()));
        ui->table_shops->setItem(i, 0, item);
        item = new QTableWidgetItem(current->get_name_shop());
        ui->table_shops->setItem(i, 1, item);
        item = new QTableWidgetItem(current->get_adress());
        ui->table_shops->setItem(i, 2, item);
        item = new QTableWidgetItem(current->get_phone());
        ui->table_shops->setItem(i, 3, item);
        current = current->get_next();
        i++;
    }
}

void MainWindow::on_add_new_clicked() { ui->menu->setCurrentIndex(5); } // добавление нового продукта - открытие формы с выбором типа продукта

// выбор типа продукта - открытие соответствующей формы для заполнения
void MainWindow::on_notebook_clicked()
{
    ui->menu->setCurrentIndex(2);
    ui->products->setCurrentIndex(0);
}
void MainWindow::on_smartphone_clicked()
{
    ui->menu->setCurrentIndex(4);
    ui->products->setCurrentIndex(1);
}
void MainWindow::on_tv_clicked()
{
    ui->menu->setCurrentIndex(3);
    ui->products->setCurrentIndex(2);
}

// отмена добавления продукта - возвращение в главное меню - очистка форм
void MainWindow::on_cancel_tv_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->artikul_tv->clear();
    ui->number_tv->clear();
    ui->cost_tv->clear();
    ui->screen_size->clear();
    ui->internet_connect->clearFocus();
    ui->number_chanels->clear();
}
void MainWindow::on_cancel_notebook_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->artikul_notebook->clear();
    ui->number_notebook->clear();
    ui->cost_notebook->clear();
    ui->memory->clear();
}
void MainWindow::on_cancel_smartphone_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->artikul_smartphone->clear();
    ui->number_smartphone->clear();
    ui->cost_smartphone->clear();
    ui->screen_size_sm->clear();
    ui->hours_working->clear();
    ui->year_production->clear();
}


void MainWindow::on_add_notebook_clicked() // отправлка формы для добавления ноутбука
{
    bool correct_data = true; // флаг корректности введенных данных

    // проверка не пустые ли строки для ввода, если пустые - флаг изменяется, строка окрашивается в красный
    if (ui->artikul_notebook->text().isEmpty()) {
        ui->artikul_notebook->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_notebook->setStyleSheet("background-color: white;"); }
    if (ui->number_notebook->text().isEmpty()) {
        ui->number_notebook->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_notebook->setStyleSheet("background-color: white;"); }
    if (ui->cost_notebook->text().isEmpty()) {
        ui->cost_notebook->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_notebook->setStyleSheet("background-color: white;"); }
    if (ui->memory->text().isEmpty()) {
        ui->memory->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->memory->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если данные корректы
        // считывание введенных данных
        QString artikul = ui->artikul_notebook->text();
        QString number = ui->number_notebook->text();
        QString cost = ui->cost_notebook->text();
        QString firma = ui->firma_notebook->currentText();
        QString memory_size = ui->memory->text();
        QString rasrad = ui->rasrad->currentText();
        QString architecture = ui->architecture->currentText();

        product* new_notebook = new notebook(artikul, number, cost, firma, memory_size, rasrad, architecture); // создание объекта с введенными данными
        current_shop->ware->add_node(new_notebook); // добавление нового узла в список

        update_table(); // обновление таблицы продуктов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_notebook->clear();
        ui->number_notebook->clear();
        ui->cost_notebook->clear();
        ui->memory->clear();

        isModicate = true; // флаг измения данных - данные изменены
    }
}

void MainWindow::on_add_smartphone_clicked() // добавление смартфона
{
    bool correct_data = true; // флаг корректности данных

    // проверка не пустые ли строки для ввода, если пустые - флаг изменяется, строка окрашивается в красный
    if (ui->artikul_smartphone->text().isEmpty()) {
        ui->artikul_smartphone->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_smartphone->setStyleSheet("background-color: white;"); }
    if (ui->number_smartphone->text().isEmpty()) {
        ui->number_smartphone->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_smartphone->setStyleSheet("background-color: white;"); }
    if (ui->cost_smartphone->text().isEmpty()) {
        ui->cost_smartphone->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_smartphone->setStyleSheet("background-color: white;"); }
    if (ui->screen_size_sm->text().isEmpty()) {
        ui->screen_size_sm->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->screen_size_sm->setStyleSheet("background-color: white;"); }
    if (ui->hours_working->text().isEmpty()) {
        ui->hours_working->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->hours_working->setStyleSheet("background-color: white;"); }
    if (ui->year_production->text().isEmpty()) {
        ui->year_production->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->year_production->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если введенные данные корректны
        // считывание данных из формы
        QString artikul = ui->artikul_smartphone->text();
        QString number = ui->number_smartphone->text();
        QString cost = ui->cost_smartphone->text();
        QString firma = ui->firma_smartphone->currentText();
        QString screen_size = ui->screen_size_sm->text();
        QString hours_working = ui->hours_working->text();
        QString year = ui->year_production->text();

        product* new_smartphone = new smartphone(artikul, number, cost, firma, screen_size, hours_working, year); // создание нового объекта
        current_shop->ware->add_node(new_smartphone);

        update_table(); // обновление таблицы продуктов

        // очистка форм и возвращение в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_smartphone->clear();
        ui->number_smartphone->clear();
        ui->cost_smartphone->clear();
        ui->screen_size_sm->clear();
        ui->hours_working->clear();
        ui->year_production->clear();

        isModicate = true; // установка флага модификации данных
    }
}

void MainWindow::on_add_tv_clicked()
{
    bool correct_data = true; // флаг корректности данных

    // проверка введенных данных - не пустые ли поля, если пустые, они окрашиваются красным
    if (ui->artikul_tv->text().isEmpty()) {
        ui->artikul_tv->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_tv->setStyleSheet("background-color: white;"); }
    if (ui->number_tv->text().isEmpty()) {
        ui->number_tv->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_tv->setStyleSheet("background-color: white;"); }
    if (ui->cost_tv->text().isEmpty()) {
        ui->cost_tv->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_tv->setStyleSheet("background-color: white;"); }
    if (ui->screen_size->text().isEmpty()) {
        ui->screen_size->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->screen_size->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если данные корректны
        // сичтывание данных из полей
        QString artikul = ui->artikul_tv->text();
        QString number = ui->number_tv->text();
        QString cost = ui->cost_tv->text();
        QString firma = ui->firma_tv->currentText();
        QString screen_size = ui->screen_size->text();
        QString internet;
        if (ui->internet_connect->isChecked()) { internet = "available"; }
        else { internet = "don't available"; }
        QString channels = ui->number_chanels->text();

        product* new_tv = new tv(artikul, number, cost, firma, screen_size, internet, channels); // создание нового объекта
        current_shop->ware->add_node(new_tv); // добавление объекта в список

        update_table(); // обновление таблицы продуктов

        // очистка формы и возвращение в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_tv->clear();
        ui->number_tv->clear();
        ui->cost_tv->clear();
        ui->screen_size->clear();
        ui->internet_connect->clearFocus();
        ui->number_chanels->clear();

        isModicate = true; // установка флага модификации
    }
}


void MainWindow::on_edit_product_clicked() // редактирование данных о продукте
{
    if (ui->table_notebooks_3->rowCount() == 0 && ui->table_smartphones_3->rowCount() == 0 && ui->table_tvs_3->rowCount() == 0) { // если в магазине нет продуктов, выдается предупреждение
         QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else { ui->menu->setCurrentIndex(14); }
}

// отмена редактирования продукта - очистка форм и возвращение в главное меню
void MainWindow::on_cancel_notebook_2_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->table_notebooks_3->clearSelection();
    ui->table_smartphones_3->clearSelection();
    ui->table_tvs_3->clearSelection();

    ui->artikul_notebook_2->clear();
    ui->number_notebook_2->clear();
    ui->cost_notebook_2->clear();
    ui->memory_2->clear();
}
void MainWindow::on_cancel_smartphone_2_clicked()
{
     ui->menu->setCurrentIndex(0);
     ui->table_notebooks_3->clearSelection();
     ui->table_smartphones_3->clearSelection();
     ui->table_tvs_3->clearSelection();

     ui->artikul_smartphone_2->clear();
     ui->number_smartphone_2->clear();
     ui->cost_smartphone_2->clear();
     ui->screen_size_sm_2->clear();
     ui->hours_working_2->clear();
     ui->year_production_2->clear();
}
void MainWindow::on_cancel_tv_2_clicked()
{
     ui->menu->setCurrentIndex(0);
     ui->table_notebooks_3->clearSelection();
     ui->table_smartphones_3->clearSelection();
     ui->table_tvs_3->clearSelection();

     ui->artikul_tv_2->clear();
     ui->number_tv_2->clear();
     ui->cost_tv_2->clear();
     ui->screen_size_2->clear();
     ui->internet_connect_2->clearFocus();
     ui->number_chanels_2->clear();
}


void MainWindow::on_change_notebook_clicked() // изменение данных ноутбука - отправка данных
{
    bool correct_data = true; // флаг корректности данных

    // проверка данных, если пустые поля - окршиваются в красный
    if (ui->artikul_notebook_2->text().isEmpty()) {
        ui->artikul_notebook_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_notebook_2->setStyleSheet("background-color: white;"); }
    if (ui->number_notebook_2->text().isEmpty()) {
        ui->number_notebook_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_notebook_2->setStyleSheet("background-color: white;"); }
    if (ui->cost_notebook_2->text().isEmpty()) {
        ui->cost_notebook_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_notebook_2->setStyleSheet("background-color: white;"); }
    if (ui->memory_2->text().isEmpty()) {
        ui->memory_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->memory_2->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если данные корректны
        int row_notebook = ui->table_notebooks_3->currentRow(); // считывание фокуса
        QTableWidgetItem *curitem = ui->table_notebooks_3->item(row_notebook, 0); // читаем id из ячейки
        int id_product = curitem->text().toInt();

        // считывание данных из формы
        QString artikul = ui->artikul_notebook_2->text();
        QString number = ui->number_notebook_2->text();
        QString cost = ui->cost_notebook_2->text();
        QString firma = ui->firma_notebook_2->currentText();
        QString memory_size = ui->memory_2->text();
        QString rasrad = ui->rasrad_2->currentText();
        QString architecture = ui->architecture_2->currentText();

        product* edit_notebook = current_shop->ware->find_node(id_product); // поиск ноутбука с таким id
        edit_notebook->set_data_product(artikul, number, cost, firma, memory_size, rasrad, architecture); // изменение данных

        update_table(); // обновление таблицы продуктов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_notebook_2->clear();
        ui->number_notebook_2->clear();
        ui->cost_notebook_2->clear();
        ui->memory_2->clear();

        // снятие фокуса с таблиц
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        isModicate = true; // установка флага модификации данных
    }
}

void MainWindow::on_change_smartphone_clicked()
{
    bool correct_data = true; // флаг корректности данных

    // проверка данных, если пустые поля - окршиваются в красный
    if (ui->artikul_smartphone_2->text().isEmpty()) {
        ui->artikul_smartphone_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_smartphone_2->setStyleSheet("background-color: white;"); }
    if (ui->number_smartphone_2->text().isEmpty()) {
        ui->number_smartphone_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_smartphone_2->setStyleSheet("background-color: white;"); }
    if (ui->cost_smartphone_2->text().isEmpty()) {
        ui->cost_smartphone_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_smartphone_2->setStyleSheet("background-color: white;"); }
    if (ui->screen_size_sm_2->text().isEmpty()) {
        ui->screen_size_sm_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->screen_size_sm_2->setStyleSheet("background-color: white;"); }
    if (ui->hours_working_2->text().isEmpty()) {
        ui->hours_working_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->hours_working_2->setStyleSheet("background-color: white;"); }
    if (ui->year_production_2->text().isEmpty()) {
        ui->year_production_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->year_production->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если данные корректны
        int row_smartphone = ui->table_smartphones_3->currentRow(); // считывание фокуса
        QTableWidgetItem *curitem = ui->table_smartphones_3->item(row_smartphone, 0); // читаем id из ячейки
        int id_product = curitem->text().toInt();

        // считывание данных из формы
        QString artikul = ui->artikul_smartphone_2->text();
        QString number = ui->number_smartphone_2->text();
        QString cost = ui->cost_smartphone_2->text();
        QString firma = ui->firma_smartphone_2->currentText();
        QString screen_size = ui->screen_size_sm_2->text();
        QString hours_working = ui->hours_working_2->text();
        QString year = ui->year_production_2->text();

        product* new_smartphone = current_shop->ware->find_node(id_product); // поиск смартфона с таким id
        new_smartphone->set_data_product(artikul, number, cost, firma, screen_size, hours_working, year); // изменение данных

        update_table(); // обновление таблицы продуктов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_smartphone_2->clear();
        ui->number_smartphone_2->clear();
        ui->cost_smartphone_2->clear();
        ui->screen_size_sm_2->clear();
        ui->hours_working_2->clear();
        ui->year_production_2->clear();

        // снятие фокуса с таблиц
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        isModicate = true; // установка флага модификации данных
    }
}

void MainWindow::on_change_tv_clicked()
{
    bool correct_data = true;// флаг корректности данных

    // проверка данных, если пустые поля - окршиваются в красный
    if (ui->artikul_tv_2->text().isEmpty()) {
        ui->artikul_tv_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->artikul_tv_2->setStyleSheet("background-color: white;"); }
    if (ui->number_tv_2->text().isEmpty()) {
        ui->number_tv_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->number_tv_2->setStyleSheet("background-color: white;"); }
    if (ui->cost_tv_2->text().isEmpty()) {
        ui->cost_tv_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->cost_tv_2->setStyleSheet("background-color: white;"); }
    if (ui->screen_size_2->text().isEmpty()) {
        ui->screen_size_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->screen_size_2->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если данные корректны
        int row_tv = ui->table_tvs_3->currentRow(); // считывание фокуса
        QTableWidgetItem *curitem = ui->table_tvs_3->item(row_tv, 0); // читаем id из ячейки
        int id_product = curitem->text().toInt();

        // считывание данных из формы
        QString artikul = ui->artikul_tv_2->text();
        QString number = ui->number_tv_2->text();
        QString cost = ui->cost_tv_2->text();
        QString firma = ui->firma_tv_2->currentText();
        QString screen_size = ui->screen_size_2->text();
        QString internet;
        if (ui->internet_connect_2->isChecked()) { internet = "available"; }
        else { internet = "don't available"; }
        QString channels = ui->number_chanels_2->text();

        product* new_tv = current_shop->ware->find_node(id_product); // поиск телевизора с таким id
        new_tv->set_data_product(artikul, number, cost, firma, screen_size, internet, channels); // изменение данных

        update_table(); // обновление таблицы продуктов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->artikul_tv_2->clear();
        ui->number_tv_2->clear();
        ui->cost_tv_2->clear();
        ui->screen_size_2->clear();
        ui->internet_connect_2->clearFocus();
        ui->number_chanels_2->clear();

        // снятие фокуса с таблиц
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        isModicate = true; // установка флага модификации данных
    }
}

void MainWindow::on_cancel_clicked() { ui->menu->setCurrentIndex(0); } // переход обратнов главное меню

// удаление продуктов
void MainWindow::on_delete_product_clicked()
{
    ui->menu->setCurrentIndex(15);
}

void MainWindow::on_change_shop_clicked()
{
    ui->menu->setCurrentIndex(9);
    update_table_shops();

}

void MainWindow::on_stay_shop_clicked() { ui->menu->setCurrentIndex(0); } // отмена изменения текущего магазина

void MainWindow::on_cancel_new_shop_clicked() { ui->menu->setCurrentIndex(0); } // отмена добавления нового магазина

void MainWindow::on_add_shop_clicked() { ui->menu->setCurrentIndex(10); } // добавление нового магазина - открытие формы

void MainWindow::on_add_new_shop_clicked() // добавление нового магазина - отправка данных из формы
{
    bool correct_data = true; // флаг корректности данных

    // проверка корректности данных, нет ли пустых полей
    if (ui->name_shop->text().isEmpty()) {
        ui->name_shop->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->name_shop->setStyleSheet("background-color: white;"); }
    if (ui->phone_shop->text().isEmpty()) {
        ui->phone_shop->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->phone_shop->setStyleSheet("background-color: white;"); }
    if (ui->adress_shop->text().isEmpty()) {
        ui->adress_shop->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->adress_shop->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если введенные данные корректны
        // считывание данных из полей
        QString name = ui->name_shop->text();
        QString phone = ui->phone_shop->text();
        QString adress = ui->adress_shop->text();

        current_shop_artikul++; //новый артикул следующего магазина
        shop* new_shop = new shop(); // создание нового магазина
        new_shop->set_data_shop(name, adress, phone);
        new_shop->set_artikul(current_shop_artikul);
        shops->add_node(new_shop); // добавление нового магазина в список
        current_shop = new_shop; // новый магазин становится текущим

        update_table(); // обновление таблицы продуктов - пустая, т.к. магазин новый
        update_table_shops(); // обновление таблицы магазинов

        // очистка формы и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->name_shop->clear();
        ui->phone_shop->clear();
        ui->adress_shop->clear();

        isModicate = true; // флаг модификации данных
    }
}

void MainWindow::on_choose_new_shop_2_clicked() // изменение текущего магазина
{
    if (ui->table_shops->rowCount() == 0) { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_shops->currentRow() == -1) { // ни один магазин не выбран
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
        else {
            int row_shop = ui->table_shops->currentRow(); // считывание фокуса
            QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула магазина для поиска
            int id_shop = curitem->text().toInt();

            current_shop = shops->find_node(id_shop); // поиск магазина с таким артикулом
            current_shop_artikul = current_shop->get_artikul();

            update_table(); // обновление таблицы продуктов
            ui->menu->setCurrentIndex(0); // возвращение в главное меню
        }
    }
}

void MainWindow::on_delete_shop_clicked() // удаление магазина
{
    if (ui->table_shops->rowCount() == 0) { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_shops->rowCount() == 1) {
            QMessageBox::critical(this, "Error", "You have only one shop!\nplease add another to delete this!");
        }
        else {
            if (ui->table_shops->currentRow() == -1) { // ни один магазин не выбран
                QMessageBox::critical(this, "Error", "No line is selected!");
            }
            else {
                int row_shop = ui->table_shops->currentRow(); // считывание фокуса
                QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула магазина для поиска
                int id_shop = curitem->text().toInt();

                shops->delete_node(id_shop); // удаление магазина с таким артикулом

                update_table(); // обновление таблицы продуктов
                update_table_shops(); // обновление таблицы магазинов

                ui->menu->setCurrentIndex(0); // возвращение в главное меню

                isModicate = true; // флаг модификации данных
            }
        }
    }
}

void MainWindow::new_file() { // создание нового файла
    if (isModicate == true) { // если данные были изменены
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();
        if(res == QMessageBox::Yes) { save_file(); } // сохранение изменений перед создание нового файла
    }

    // создание новой сети магазинов содним магазином по умолчанию
    shops->clear_list();
    current_shop->ware->clear_list();
    shops->add_node(current_shop);

    update_table(); // обновление таблицы продуктов
    update_table_shops(); // обновление таблицы магазинов
    current_file = "";

    isModicate = false; // сбрасываем флаг модификации данных - файл пустой
}

void MainWindow::save_file() { // сохранение файла
    QFile file;

    if(current_file == "") { save_as(); } // если никакой файл не открыт, то просим пользователя создать
    else
    {
        file.setFileName(current_file);
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        write_in_file(file); // запись в файл
        isModicate = false;
        file.close();
    }
}

void MainWindow::write_in_file(QFile &file) { // хапись в файл
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << shops->get_count_all_shops() << endl; // запись количества магазинов
    shop* write_current_shop = shops->get_head();
    while (write_current_shop != nullptr) { // цикл по магазинам
//        stream << write_current_shop->get_artikul() << endl;
        stream << write_current_shop->get_name_shop() << endl;
        stream << write_current_shop->get_adress() << endl;
        stream << write_current_shop->get_phone() << endl;
        list_product* write_current_products = write_current_shop->get_ware();
        stream << write_current_products->get_count() << endl; // запись количества продуктов магазина
        product* write_current_product = write_current_products->get_head();
        while (write_current_product != nullptr) { // цикл по продуктам магазина
            stream << write_current_product->get_category() << endl;
            stream << write_current_product->get_iid() << endl;
            stream << write_current_product->get_number() << endl;
            stream << write_current_product->get_cost() << endl;
            stream << write_current_product->get_firma() << endl;
            stream << write_current_product->get_first() << endl;
            stream << write_current_product->get_second() << endl;
            stream << write_current_product->get_third() << endl;
            write_current_product = write_current_product->next; // следующий продукт
        }
        write_current_shop = write_current_shop->get_next(); // следующий магазин
    }
}

void MainWindow::save_as() { // сохранение под новым именем
    QFile file;

    QString fileName = QFileDialog::getSaveFileName(this, "Save as ...", QDir::homePath(), "Text file (*.txt)");
    if (!fileName.isEmpty())
    {
        current_file = fileName;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);

        write_in_file(file); // запись в файл
        isModicate = false;
        file.close();
    }
}

void MainWindow::exit_prog() { // закрытие программы
    if (isModicate == true) {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes) { save_file(); } // сохранение изменений перед закрытием
    }

    close();
}

void MainWindow::about_program() { // о программе
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("The program by Svetlana Rudneva\nAll roots reserved");
    msgBox.exec();
}

void MainWindow::help() { // справка
    QMessageBox msgBox;
    msgBox.setWindowTitle("How use this app");
    msgBox.setText("This program is very easy in using!\nYou will get success!\nWe belive that you will enjoy!");
    msgBox.exec();
}

void MainWindow::open_file() { // открытие файла
    if (isModicate == true) { // если текущий файл был изменен
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes) { save_file(); } // сохранение изменений перед открытием
    }

    // очистка списков и таблиц
    shops->clear_list();
    current_shop->ware->clear_list();
    update_table();
    update_table_shops();
    isModicate = false;

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Text file (*.txt)");

    if(!fileName.isEmpty()) // если файл не пустой
    {
        current_file = fileName;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        int count_shops = (stream.readLine()).toInt(); // считываем количество магазинов

        for(int i = 0; i < count_shops; i++) {

//            int artikul = (stream.readLine()).toInt();
            QString name = stream.readLine();
            QString adress = stream.readLine();
            QString phone = stream.readLine();

            int count_products = (stream.readLine()).toInt(); // считываем количество продуктов в конкретном магазине
            shop* current = new shop(); // создание магазина
            current->set_data_shop(name, adress, phone);
            current->set_artikul(current_shop_artikul);
            current_shop_artikul++;

            for (int j = 0; j < count_products; j++) {
                // считывание данных
                QString category = stream.readLine();
                QString iid = stream.readLine();
                QString number = stream.readLine();
                QString cost = stream.readLine();
                QString firma = stream.readLine();
                // создание узлов и добавление их в список
                if (category == "Notebook") {
                    QString memory_size = stream.readLine();
                    QString rasrad = stream.readLine();
                    QString architecture = stream.readLine();
                    product* new_product = new notebook(iid, number, cost, firma, memory_size, rasrad, architecture);
                    current->ware->add_node(new_product);

                }
                if (category == "Smartphone") {
                    QString screen_size = stream.readLine();
                    QString hours_working = stream.readLine();
                    QString year_production = stream.readLine();
                    product* new_product = new smartphone(iid, number, cost, firma, screen_size, hours_working, year_production);
                    current->ware->add_node(new_product);
                }
                if (category == "TV") {
                    QString screen_size = stream.readLine();
                    QString internet_connect = stream.readLine();
                    QString number_channels = stream.readLine();
                    product* new_product = new tv(iid, number, cost, firma, screen_size, internet_connect, number_channels);
                    current->ware->add_node(new_product);
                }
            }
            shops->add_node(current); // добавление магазина в список
            current_shop = current; // изменение текушего магазина
        }

        update_table(); // обновление таблицы продуктов
        update_table_shops(); // обновление таблицы магазинов
        isModicate = false; // данные еще не изменялись
        file.close(); // закрытие файла
    }
}

void MainWindow::on_cancel_new_shop_2_clicked() { ui->menu->setCurrentIndex(0); } // отмена добавления нового магазина


void MainWindow::on_edit_shop_done_clicked() //  изменение данных магазина - отправка формы
{
    bool correct_data = true; // флаг корректности данных

    // проверка полей
    if (ui->name_shop_2->text().isEmpty()) {
        ui->name_shop_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->name_shop_2->setStyleSheet("background-color: white;"); }
    if (ui->phone_shop_2->text().isEmpty()) {
        ui->phone_shop_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->phone_shop_2->setStyleSheet("background-color: white;"); }
    if (ui->adress_shop_2->text().isEmpty()) {
        ui->adress_shop_2->setStyleSheet("background-color: red;");
        correct_data = false;
    }
    else { ui->adress_shop_2->setStyleSheet("background-color: white;"); }

    if (correct_data == true) { // если введенные данные корректы
        // считывание данных из полей
        QString name = ui->name_shop_2->text();
        QString phone = ui->phone_shop_2->text();
        QString adress = ui->adress_shop_2->text();

        int row_shop = ui->table_shops->currentRow(); // считывание фокуса
        QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0); // считывание артикула
        int id_shop = curitem->text().toInt();

        shop* edit_shop = shops->find_node(id_shop); // поиск изменяемого магазина
        edit_shop->set_data_shop(name, adress, phone); // установка новых значений
        if (current_shop_artikul == edit_shop->get_artikul()) { current_shop = edit_shop; } // если текущий артикул совпадает с артикулом изменяемого магазина

        update_table_shops(); // обновление таблицы магазинов

        // очистка формыти переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->name_shop_2->clear();
        ui->phone_shop_2->clear();
        ui->adress_shop_2->clear();

        isModicate = true; // данные изменены
    }
}

void MainWindow::on_edit_shop_data_clicked() // изменение данных магазина
{
    int row_shop = ui->table_shops->currentRow(); // считывание фокуса
    if (row_shop != -1) {
         ui->menu->setCurrentIndex(11); // открчытие формы
        QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0);
        int id_shop = curitem->text().toInt();
        shop* edit_shop = shops->find_node(id_shop); // поиск магазина

        // запись в форму текущих данных
        ui->name_shop_2->setText(edit_shop->get_name_shop());
        ui->phone_shop_2->setText(edit_shop->get_phone());
        ui->adress_shop_2->setText(edit_shop->get_adress());
    }
    else {
        QMessageBox::critical(this, "Error", "Choose the shop!");
    }
}

void MainWindow::on_search_product_clicked() { ui->menu->setCurrentIndex(1); } // поиск продуктов

void MainWindow::on_cancel_search_clicked() // отмена поиска - переход в главное меню
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}

void MainWindow::on_search_by_cost_clicked() // поиск по стоимости - открытие формы поиска
{
    ui->menu->setCurrentIndex(12);
    ui->min_cost->setText("0");
    ui->max_cost->setText("10000000");
    ui->tables->setCurrentIndex(1);
}

void MainWindow::on_search_cost_product_clicked() // поиск по стоимости - отправка данных
{
    bool correct_data = true; // флаг корректности данных

    // проверка корректности данных
    if (ui->min_cost->text().isEmpty()) {
        correct_data = false;
        ui->min_cost->setStyleSheet("background-color: red;");
    }
    else { ui->min_cost->setStyleSheet("background-color: white;");
    }
    if (ui->max_cost->text().isEmpty()) {
        correct_data = false;
        ui->max_cost->setStyleSheet("background-color: red;");
    }
    else { ui->max_cost->setStyleSheet("background-color: white;"); }
    if ((ui->min_cost->text()).toFloat() > (ui->max_cost->text()).toFloat()) { // минимальная стоимость должна не превышать максимальную
        correct_data = false;
        ui->min_cost->setStyleSheet("background-color: red;");
        ui->max_cost->setStyleSheet("background-color: red;");
        QMessageBox::critical(this, "Error", "You entered wrong cost characteristics!");
    }
    else {
        ui->min_cost->setStyleSheet("background-color: white;");
        ui->max_cost->setStyleSheet("background-color: white;");
    }

    if (correct_data == true) { // если данные корректны
        // считывание данных из полей
        float minimum = (ui->min_cost->text()).toFloat();
        float maximum = (ui->max_cost->text()).toFloat();
        QString type = ui->type_product->currentText();
        bool all_shops_search = ui->where_search->isChecked();

        int count_results = 0; // количество продуктов, соответствующих критериям поиска
        if (type == "Notebook" || type == "Smartphone" || type == "TV") { // если выбран кокретный тип продукта
            QStringList Title_product; // заголовок таблицы результатов
            if (type == "Notebook") {
                Title_product << "ID"
                              << "Artikul"
                              << "Number"
                              << "Cost"
                              << "Firma"
                              << "Memory size"
                              << "Rasrad"
                              << "Architecture";
            }
            if (type == "Smartphone") {
                Title_product << "ID"
                                 << "Artikul"
                                 << "Number"
                                 << "Cost"
                                 << "Firma"
                                 << "Screen size"
                                 << "Hours working"
                                 << "Year production";
            }
            if (type == "TV") {
                Title_product << "ID"
                         << "Artikul"
                         << "Number"
                         << "Cost"
                         << "Firma"
                         << "Screen size"
                         << "Internet connect"
                         << "Number channels";
            }

            ui->search_table->setHorizontalHeaderLabels(Title_product);

            if (all_shops_search == true) { // если выбран критерий поиска по всем магазинам сети
                shop* search_shop = shops->get_head();
                QTableWidgetItem *item;
                int i = 0; // для заполнения таблицы - счетчик строк
                count_results = 0; // количество результатов
                ui->search_table->setRowCount(count_results);
                while (search_shop != nullptr) { // цикл по магазинам
                    list_product* search_products = search_shop->get_ware();
                    product* current_search = search_products->head;
                    while (current_search != nullptr) { // цикл по продуктам магазина
                        if ((minimum <= (current_search->get_cost()).toFloat()) && ((current_search->get_cost()).toFloat() <= maximum) && (current_search->get_category() == type)) { // критерия подходящих продуктов
                            count_results++;
                            ui->search_table->setRowCount(count_results); // добавление строк

                            // заполнение таблицы
                            item = new QTableWidgetItem(QString::number(current_search->get_current()));
                            ui->search_table->setItem(i, 0, item);
                            item = new QTableWidgetItem(current_search->get_iid());
                            ui->search_table->setItem(i, 1, item);
                            item = new QTableWidgetItem(current_search->get_number());
                            ui->search_table->setItem(i, 2, item);
                            item = new QTableWidgetItem(current_search->get_cost());
                            ui->search_table->setItem(i, 3, item);
                            item = new QTableWidgetItem(current_search->get_firma());
                            ui->search_table->setItem(i, 4, item);
                            item = new QTableWidgetItem(current_search->get_first());
                            ui->search_table->setItem(i, 5, item);
                            item = new QTableWidgetItem(current_search->get_second());
                            ui->search_table->setItem(i, 6, item);
                            item = new QTableWidgetItem(current_search->get_third());
                            ui->search_table->setItem(i, 7, item);

                            i++;
                        }
                        current_search = current_search->next;
                    }
                    search_shop = search_shop->get_next();
                }
                ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных продуктов
            }
            else { // поиск только в текущем магазине
                list_product* search_products = current_shop->get_ware(); // список продуктов текущего магазина
                product* current_search = search_products->head;
                QTableWidgetItem *item;
                int i = 0;
                count_results = 0;
                ui->search_table->setRowCount(count_results);
                while (current_search != nullptr) { // цикл по списку продуктов текущего магазина
                    if ((minimum <= (current_search->get_cost()).toFloat()) && ((current_search->get_cost()).toFloat() <= maximum) && (current_search->get_category() == type)) { // проверка критериев поиска
                        count_results++;
                        ui->search_table->setRowCount(count_results); // добавление строк

                        // заполнение таблицы
                        item = new QTableWidgetItem(QString::number(current_search->get_current()));
                        ui->search_table->setItem(i, 0, item);
                        item = new QTableWidgetItem(current_search->get_iid());
                        ui->search_table->setItem(i, 1, item);
                        item = new QTableWidgetItem(current_search->get_number());
                        ui->search_table->setItem(i, 2, item);
                        item = new QTableWidgetItem(current_search->get_cost());
                        ui->search_table->setItem(i, 3, item);
                        item = new QTableWidgetItem(current_search->get_firma());
                        ui->search_table->setItem(i, 4, item);
                        item = new QTableWidgetItem(current_search->get_first());
                        ui->search_table->setItem(i, 5, item);
                        item = new QTableWidgetItem(current_search->get_second());
                        ui->search_table->setItem(i, 6, item);
                        item = new QTableWidgetItem(current_search->get_third());
                        ui->search_table->setItem(i, 7, item);

                        i++;
                    }
                    current_search = current_search->next;
                }
            ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных продуктов
            }
        }
        else { // поиск среди продуктов всех типов
            QStringList Title; // заголовок таблицы результатов
            Title << "ID"
                  << "Type"
                  << "Artikul"
                  << "Number"
                  << "Cost"
                  << "Firma"
                  << "Optional";
            ui->search_table->setColumnCount(7);
            ui->search_table->setHorizontalHeaderLabels(Title);

            if (all_shops_search == true) { // поиск по всем магазинам сети
                shop* search_shop = shops->get_head();
                QTableWidgetItem *item;
                int i = 0; // счетчик строк для заполнения таблицы
                count_results = 0; // количество найденных продуктов
                ui->search_table->setRowCount(count_results);
                while (search_shop != nullptr) { // цикл по магазинам
                    list_product* search_products = search_shop->get_ware();
                    product* current_search = search_products->head;

                    while (current_search != nullptr) { // цикл по списку продуктов магазина
                        if ((minimum <= (current_search->get_cost()).toFloat()) && ((current_search->get_cost()).toFloat() <= maximum)) {
                            count_results++;
                            ui->search_table->setRowCount(count_results);

                            // заполнение таблицы
                            item = new QTableWidgetItem(QString::number(current_search->get_current()));
                            ui->search_table->setItem(i, 0, item);
                            item = new QTableWidgetItem(current_search->get_category());
                            ui->search_table->setItem(i, 1, item);
                            item = new QTableWidgetItem(current_search->get_iid());
                            ui->search_table->setItem(i, 2, item);
                            item = new QTableWidgetItem(current_search->get_number());
                            ui->search_table->setItem(i, 3, item);
                            item = new QTableWidgetItem(current_search->get_cost());
                            ui->search_table->setItem(i, 4, item);
                            item = new QTableWidgetItem(current_search->get_firma());
                            ui->search_table->setItem(i, 5, item);
                            item = new QTableWidgetItem(current_search->get_first() + ", " + current_search->get_second() + ", " + current_search->get_third());
                            ui->search_table->setItem(i, 6, item);

                            i++;
                        }
                        current_search = current_search->next;
                    }
                    search_shop = search_shop->get_next();
                }
                ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных продуктов
            }
            else { // поиск по текущему магазину
                list_product* search_products = current_shop->get_ware(); // список продуктов магазина
                product* current_search = search_products->head;
                QTableWidgetItem *item;
                int i = 0;
                count_results = 0;
                ui->search_table->setRowCount(count_results);
                while (current_search != nullptr) { // цикл по продуктам магазина
                    if ((minimum <= (current_search->get_cost()).toFloat()) && ((current_search->get_cost()).toFloat() <= maximum)) {
                        count_results++;

                        // заполнение таблицы
                        ui->search_table->setRowCount(count_results);
                        item = new QTableWidgetItem(QString::number(current_search->get_current()));
                        ui->search_table->setItem(i, 0, item);
                        item = new QTableWidgetItem(current_search->get_category());
                        ui->search_table->setItem(i, 1, item);
                        item = new QTableWidgetItem(current_search->get_iid());
                        ui->search_table->setItem(i, 2, item);
                        item = new QTableWidgetItem(current_search->get_number());
                        ui->search_table->setItem(i, 3, item);
                        item = new QTableWidgetItem(current_search->get_cost());
                        ui->search_table->setItem(i, 4, item);
                        item = new QTableWidgetItem(current_search->get_firma());
                        ui->search_table->setItem(i, 5, item);
                        item = new QTableWidgetItem(current_search->get_first() + ", " + current_search->get_second() + ", " + current_search->get_third());
                        ui->search_table->setItem(i, 6, item);

                        i++;
                    }
                    current_search = current_search->next;
                }
            ui->number_res_search->setText(QString::number(count_results)); // отображение количества найденных результатов
            }
        }
        // установка данных по умолчанию
        ui->min_cost->setText("0");
        ui->max_cost->setText("10000000");
    }
}
void MainWindow::on_cancel_search_2_clicked() // отмена поиска
{
    ui->menu->setCurrentIndex(0);
    ui->tables->setCurrentIndex(0);
}

void MainWindow::on_search_by_firm_clicked() // поиск по фирме - отображение формы
{
    ui->menu->setCurrentIndex(13);
    ui->tables->setCurrentIndex(1);
}

void MainWindow::on_search_firm_product_clicked() // поиск по фирме - отправка данных из формы
{
   bool correct_data = true; // флаг корректности данных

   // проверка корректности введенных данных
   if (ui->name_firm->text().isEmpty()) {
       correct_data = false;
       ui->name_firm->setStyleSheet("background-color: red;");
   }
   else { ui->name_firm->setStyleSheet("background-color: white;"); }

   if (correct_data == true) { // если данные корректны
       // считывание данных
       QString search_firm = ui->name_firm->text();
       bool all_shops_search = ui->where_search_2->isChecked();
       QString type = ui->type_product_2->currentText();

       int count_results = 0;
       ui->search_table->setRowCount(count_results);
       if (type == "Notebook" || type == "Smartphone" || type == "TV") { // поиск по конкретному типу продукта
           QStringList Title_product;
           if (type == "Notebook") {
               Title_product << "ID"
                             << "Artikul"
                             << "Number"
                             << "Cost"
                             << "Firma"
                             << "Memory size"
                             << "Rasrad"
                             << "Architecture";
           }
           if (type == "Smartphone") {
               Title_product << "ID"
                                << "Artikul"
                                << "Number"
                                << "Cost"
                                << "Firma"
                                << "Screen size"
                                << "Hours working"
                                << "Year production";
           }
           if (type == "TV") {
               Title_product << "ID"
                        << "Artikul"
                        << "Number"
                        << "Cost"
                        << "Firma"
                        << "Screen size"
                        << "Internet connect"
                        << "Number channels";
           }
           ui->search_table->setHorizontalHeaderLabels(Title_product);

           if (all_shops_search == true) { // поиск по всем магазинам сети
               shop* search_shop = shops->get_head();
               QTableWidgetItem *item;
               int i = 0;
               count_results = 0;
               ui->search_table->setRowCount(count_results);
               while (search_shop != nullptr) { // цикл по магазинам
                   list_product* search_products = search_shop->get_ware();
                   product* current_search = search_products->head;
                   while (current_search != nullptr) { // цикл по продуктам магазина
                       if (current_search->get_firma() == search_firm && (current_search->get_category() == type)) {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_number());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_cost());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_first());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_second());
                           ui->search_table->setItem(i, 6, item);
                           item = new QTableWidgetItem(current_search->get_third());
                           ui->search_table->setItem(i, 7, item);

                           i++;
                       }
                       current_search = current_search->next;
                   }
                   search_shop = search_shop->get_next();
               }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов поиска
           }
           else { // поиск только в текущем магазине
               list_product* search_products = current_shop->get_ware(); // список продуктов магазина
               product* current_search = search_products->head;
               QTableWidgetItem *item;
               int i = 0;
               count_results = 0;
               ui->search_table->setRowCount(count_results);
               while (current_search != nullptr) { // цикл по продуктам
                   if (current_search->get_firma() == search_firm && (current_search->get_category() == type)) {
                       count_results++;
                       ui->search_table->setRowCount(count_results);

                       // заполнение таблицы
                       item = new QTableWidgetItem(QString::number(current_search->get_current()));
                       ui->search_table->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_iid());
                       ui->search_table->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_number());
                       ui->search_table->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_cost());
                       ui->search_table->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_firma());
                       ui->search_table->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_first());
                       ui->search_table->setItem(i, 5, item);
                       item = new QTableWidgetItem(current_search->get_second());
                       ui->search_table->setItem(i, 6, item);
                       item = new QTableWidgetItem(current_search->get_third());
                       ui->search_table->setItem(i, 7, item);

                       i++;
                   }
                   current_search = current_search->next;
               }
           ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
           }
       }
       else { // поиск среди продуктов всех типов
           QStringList Title;
           Title << "ID"
                 << "Type"
                 << "Artikul"
                 << "Number"
                 << "Cost"
                 << "Firma"
                 << "Optional";
           ui->search_table->setColumnCount(7);
           ui->search_table->setHorizontalHeaderLabels(Title);

           if (all_shops_search == true) { // поиск во всех магазинах сети
               shop* search_shop = shops->get_head();
               QTableWidgetItem *item;
               int i = 0;
               count_results = 0;
               ui->search_table->setRowCount(count_results);
               while (search_shop != nullptr) { // цикл по магазинам
                   list_product* search_products = search_shop->get_ware();
                   product* current_search = search_products->head;
                   while (current_search != nullptr) { // цикл по продуктам
                       if (current_search->get_firma() == search_firm) {
                           count_results++;
                           ui->search_table->setRowCount(count_results);

                           // заполнение таблицы
                           item = new QTableWidgetItem(QString::number(current_search->get_current()));
                           ui->search_table->setItem(i, 0, item);
                           item = new QTableWidgetItem(current_search->get_category());
                           ui->search_table->setItem(i, 1, item);
                           item = new QTableWidgetItem(current_search->get_iid());
                           ui->search_table->setItem(i, 2, item);
                           item = new QTableWidgetItem(current_search->get_number());
                           ui->search_table->setItem(i, 3, item);
                           item = new QTableWidgetItem(current_search->get_cost());
                           ui->search_table->setItem(i, 4, item);
                           item = new QTableWidgetItem(current_search->get_firma());
                           ui->search_table->setItem(i, 5, item);
                           item = new QTableWidgetItem(current_search->get_first() + ", " + current_search->get_second() + ", " + current_search->get_third());
                           ui->search_table->setItem(i, 6, item);

                           i++;
                       }
                       current_search = current_search->next;
                   }
                   search_shop = search_shop->get_next();
               }
               ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
           }
           else { // поиск только в текущем магазине
               list_product* search_products = current_shop->get_ware(); // список продуктов текущего магазина
               product* current_search = search_products->head;
               QTableWidgetItem *item;
               int i = 0;
               count_results = 0;

               while (current_search != nullptr) { // цикл по продуктам магазина
                   if (current_search->get_firma() == search_firm) {
                       count_results++;
                       ui->search_table->setRowCount(count_results);

                       // заполнение таблицы
                       item = new QTableWidgetItem(QString::number(current_search->get_current()));
                       ui->search_table->setItem(i, 0, item);
                       item = new QTableWidgetItem(current_search->get_category());
                       ui->search_table->setItem(i, 1, item);
                       item = new QTableWidgetItem(current_search->get_iid());
                       ui->search_table->setItem(i, 2, item);
                       item = new QTableWidgetItem(current_search->get_number());
                       ui->search_table->setItem(i, 3, item);
                       item = new QTableWidgetItem(current_search->get_cost());
                       ui->search_table->setItem(i, 4, item);
                       item = new QTableWidgetItem(current_search->get_firma());
                       ui->search_table->setItem(i, 5, item);
                       item = new QTableWidgetItem(current_search->get_first() + ", " + current_search->get_second() + ", " + current_search->get_third());
                       ui->search_table->setItem(i, 6, item);

                       i++;
                   }
                   current_search = current_search->next;
               }
           ui->number_res_search->setText(QString::number(count_results)); // отображение количества результатов
           }
       }
   }
}


void MainWindow::on_edit_notebook_2_clicked()
{
    ui->products->setCurrentIndex(0);
    if (ui->table_notebooks_3->rowCount() == 0) { // если в магазине нет продуктов, выдается предупреждение
         QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        int row_notebook = ui->table_notebooks_3->currentRow();

        if (row_notebook != -1) { // если редактируется ноутбук
            QTableWidgetItem *curitem = ui->table_notebooks_3->item(row_notebook, 0); // считывание ячейки, содержащей id
            ui->menu->setCurrentIndex(6); // открытие формы для редактирования
            int id_product = curitem->text().toInt(); // получение id подукта

            product* edit_product = current_shop->ware->find_node(id_product); // поиск узла с данным id

            // запись в форму текущих данных
            ui->artikul_notebook_2->setText(edit_product->get_iid());
            ui->number_notebook_2->setText(edit_product->get_number());
            ui->cost_notebook_2->setText(edit_product->get_cost());
            ui->firma_notebook_2->setCurrentText(edit_product->get_firma());
            ui->memory_2->setText(edit_product->get_first());
            ui->rasrad_2->setCurrentText(edit_product->get_second());
            ui->architecture_2->setCurrentText(edit_product->get_third());
        }
    }
}

void MainWindow::on_editsmartphone_clicked()
{
    ui->products->setCurrentIndex(1);
    if (ui->table_smartphones_3->rowCount() == 0) { // если в магазине нет продуктов, выдается предупреждение
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        int row_smartphone = ui->table_smartphones_3->currentRow();

        if (row_smartphone != -1) { // если редактируется смартфон
            QTableWidgetItem *curitem = ui->table_smartphones_3->item(row_smartphone, 0); // считывание ячейки, содержащей id
            ui->menu->setCurrentIndex(7); // открытие формы для редактирования
            int id_product = curitem->text().toInt(); // получение id подукта

            product* edit_product = current_shop->ware->find_node(id_product); // поиск узла с данным id

            // запись в форму текущих данных
            ui->artikul_smartphone_2->setText(edit_product->get_iid());
            ui->number_smartphone_2->setText(edit_product->get_number());
            ui->cost_smartphone_2->setText(edit_product->get_cost());
            ui->firma_smartphone_2->setCurrentText(edit_product->get_firma());
            ui->screen_size_sm_2->setText(edit_product->get_first());
            ui->hours_working_2->setText(edit_product->get_second());
            ui->year_production_2->setText(edit_product->get_third());
        }
    }
}

void MainWindow::on_edit_tv_2_clicked()
{
    ui->products->setCurrentIndex(2);
    if (ui->table_tvs_3->rowCount() == 0) { // если в магазине нет продуктов, выдается предупреждение
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        int row_tv = ui->table_tvs_3->currentRow();

        if (row_tv != -1) { // если редактируется телевизор
            QTableWidgetItem *curitem = ui->table_tvs_3->item(row_tv, 0); // считывание ячейки, содержащей id
            ui->menu->setCurrentIndex(8); // открытие формы для редактирования
            int id_product = curitem->text().toInt(); // получение id подукта

            product* edit_product = current_shop->ware->find_node(id_product); // поиск узла с данным id

            // запись в форму текущих данных
            ui->artikul_tv_2->setText(edit_product->get_iid());
            ui->number_tv_2->setText(edit_product->get_number());
            ui->cost_tv_2->setText(edit_product->get_cost());
            ui->firma_tv_2->setCurrentText(edit_product->get_firma());
            ui->screen_size_2->setText(edit_product->get_first());
            if (edit_product->get_second() == "available") { ui->internet_connect_2->setChecked(true); }
            else { ui->internet_connect_2->setChecked(false); }
            ui->number_chanels_2->setText(edit_product->get_third());
        }
    }
}

void MainWindow::on_cancel_edit_clicked()
{
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_delete_notebook_clicked()
{
    if (ui->table_notebooks_3->rowCount() == 0) { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        // считывание фокусов
        int row_notebook = ui->table_notebooks_3->currentRow();

        int id_product = 0;
        if (row_notebook != -1) {
            QTableWidgetItem *curitem = ui->table_notebooks_3->item(row_notebook, 0);
            id_product = curitem->text().toInt();
            current_shop->ware->delete_node(id_product);
        }

        // очистка фокусов и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        update_table(); // обновление таблицы продуктов
    }
}

void MainWindow::on_delete_smartphone_clicked()
{
    if (ui->table_smartphones_3->rowCount() == 0) { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        int row_smartphone = ui->table_smartphones_3->currentRow();

        int id_product = 0;
        if (row_smartphone != -1) { // если фокус на таблице смартфонов
            QTableWidgetItem *curitem = ui->table_smartphones_3->item(row_smartphone, 0);
            id_product = curitem->text().toInt();
            current_shop->ware->delete_node(id_product);
        }

        // очистка фокусов и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        update_table(); // обновление таблицы продуктов
    }
}

void MainWindow::on_delete_tv_clicked()
{
    if (ui->table_tvs_3->rowCount() == 0) { // таблица пустая
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        int row_tv = ui->table_tvs_3->currentRow();
        int id_product = 0;

        if (row_tv != -1) { // если фокус на таблице телевизоров
            QTableWidgetItem *curitem = ui->table_tvs_3->item(row_tv, 0);
            id_product = curitem->text().toInt();
            current_shop->ware->delete_node(id_product);
        }

        // очистка фокусов и переход в главное меню
        ui->menu->setCurrentIndex(0);
        ui->table_notebooks_3->clearSelection();
        ui->table_smartphones_3->clearSelection();
        ui->table_tvs_3->clearSelection();

        update_table(); // обновление таблицы продуктов
    }
}

void MainWindow::on_cancel_delete_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->table_notebooks_3->clearSelection();
    ui->table_smartphones_3->clearSelection();
    ui->table_tvs_3->clearSelection();
}

void MainWindow::on_cancel_search_3_clicked()
{
     ui->menu->setCurrentIndex(0);
}
