#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, int m_artikul, shop_list* m_shops, shop* m_current_shop, bool m_isModificate, QString m_current_file)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), shops(m_shops), current_shop_artikul(m_artikul), current_shop(m_current_shop), isModicate(m_isModificate), current_file(m_current_file)
{
    ui->setupUi(this);

    setWindowTitle(tr("%1[*]").arg("Information about electronic shop"));

    shops = new shop_list();
    current_shop = new shop();
    shops->add_node(current_shop);

    ui->table_notebooks->setColumnCount(8);
    ui->table_notebooks->setRowCount(0);
    QStringList Title_notebook;
    Title_notebook << "ID"
                  << "Artikul"
                  << "Number"
                  << "Cost"
                  << "Firma"
                  << "Memory size"
                  << "Rasrad"
                  << "Architecture";
    ui->table_notebooks->setHorizontalHeaderLabels(Title_notebook);
    ui->table_notebooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_notebooks->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_notebooks->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_notebooks->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->table_smartphones->setColumnCount(8);
    ui->table_smartphones->setRowCount(0);
    QStringList Title_smartphone;
    Title_smartphone << "ID"
                     << "Artikul"
                     << "Number"
                     << "Cost"
                     << "Firma"
                     << "Screen size"
                     << "Hours working"
                     << "Year production";
    ui->table_smartphones->setHorizontalHeaderLabels(Title_smartphone);
    ui->table_smartphones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_smartphones->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_smartphones->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_smartphones->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->table_tvs->setColumnCount(8);
    ui->table_tvs->setRowCount(0);
    QStringList Title_tv;
    Title_tv << "ID"
             << "Artikul"
             << "Number"
             << "Cost"
             << "Firma"
             << "Screen size"
             << "Internet connect"
             << "Number channels";
    ui->table_tvs->setHorizontalHeaderLabels(Title_tv);
    ui->table_tvs->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_tvs->setSelectionMode(QAbstractItemView::SingleSelection); //Запрет выбора больше одной строки
    ui->table_tvs->setSelectionBehavior(QAbstractItemView::SelectRows); //Выбор только строк
    ui->table_tvs->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->menu->setCurrentIndex(0);

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

    ui->count_notebooks->setText(QString::number(current_shop->get_ware()->get_count_notebooks()));
    ui->count_smartphones->setText(QString::number(current_shop->get_ware()->get_count_smartphones()));
    ui->count_tvs->setText(QString::number(current_shop->get_ware()->get_count_tvs()));
    ui->all_products->setText(QString::number(current_shop->get_ware()->get_count()));

    ui->table_shops->setColumnCount(4);
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

    ui->number_shops->setText(QString::number(shops->get_count_all_shops()));

    ui->menuFile->addAction("Create new", this, SLOT(new_file()));
    ui->menuFile->addAction("Open file", this, SLOT(open_file()));
    ui->menuFile->addAction("Save", this, SLOT(save_file()));
    ui->menuFile->addAction("Save as", this, SLOT(save_as()));
    ui->menuFile->addAction("Exit", this, SLOT(exit_prog()));

    ui->menuHelp->addAction("How use this program...", this, SLOT(help()));
    ui->menuHelp->addAction("About program", this, SLOT(about_program()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_table() {
    int number_notebooks = current_shop->get_ware()->get_count_notebooks();
    int number_smartphones = current_shop->get_ware()->get_count_smartphones();
    int number_tvs = current_shop->get_ware()->get_count_tvs();

    product* current = current_shop->ware->get_head();

    ui->table_notebooks->setRowCount(number_notebooks);
    ui->table_smartphones->setRowCount(number_smartphones);
    ui->table_tvs->setRowCount(number_tvs);

    ui->count_notebooks->setText(QString::number(current_shop->get_ware()->get_count_notebooks()));
    ui->count_smartphones->setText(QString::number(current_shop->get_ware()->get_count_smartphones()));
    ui->count_tvs->setText(QString::number(current_shop->get_ware()->get_count_tvs()));
    ui->all_products->setText(QString::number(current_shop->get_ware()->get_count()));

    int i1 = 0, i2 = 0, i3 = 0;
    while (current != nullptr){
        QTableWidgetItem *item;

        if (current->get_category() == "Notebook") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_notebooks->setItem(i1, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_notebooks->setItem(i1, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_notebooks->setItem(i1, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_notebooks->setItem(i1, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_notebooks->setItem(i1, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_notebooks->setItem(i1, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_notebooks->setItem(i1, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_notebooks->setItem(i1, 7, item);
            i1++;
        }

        if (current->get_category() == "Smartphone") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_smartphones->setItem(i2, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_smartphones->setItem(i2, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_smartphones->setItem(i2, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_smartphones->setItem(i2, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_smartphones->setItem(i2, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_smartphones->setItem(i2, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_smartphones->setItem(i2, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_smartphones->setItem(i2, 7, item);
            i2++;
        }

        if (current->get_category() == "TV") {
            item = new QTableWidgetItem(QString::number(current->get_current()));
            ui->table_tvs->setItem(i3, 0, item);
            item = new QTableWidgetItem(current->get_iid());
            ui->table_tvs->setItem(i3, 1, item);
            item = new QTableWidgetItem(current->get_number());
            ui->table_tvs->setItem(i3, 2, item);
            item = new QTableWidgetItem(current->get_cost());
            ui->table_tvs->setItem(i3, 3, item);
            item = new QTableWidgetItem(current->get_firma());
            ui->table_tvs->setItem(i3, 4, item);
            item = new QTableWidgetItem(current->get_first());
            ui->table_tvs->setItem(i3, 5, item);
            item = new QTableWidgetItem(current->get_second());
            ui->table_tvs->setItem(i3, 6, item);
            item = new QTableWidgetItem(current->get_third());
            ui->table_tvs->setItem(i3, 7, item);
            i3++;
        }

        current = current->get_next();
    }
    ui->table_notebooks->clearSelection();
    ui->table_smartphones->clearSelection();
    ui->table_tvs->clearSelection();
}

void MainWindow::update_table_shops() {
    ui->number_shops->setText(QString::number(shops->get_count_all_shops()));
    ui->table_shops->setRowCount(current_shop->get_number_shop());
    shop* current = shops->get_head();
    int i = 0;
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

void MainWindow::on_add_new_clicked()
{
    ui->menu->setCurrentIndex(5);
}

void MainWindow::on_notebook_clicked()
{
    ui->menu->setCurrentIndex(2);
}

void MainWindow::on_smartphone_clicked()
{
    ui->menu->setCurrentIndex(4);
}

void MainWindow::on_tv_clicked()
{
    ui->menu->setCurrentIndex(3);
}

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

void MainWindow::on_add_notebook_clicked()
{
    bool correct_data = true;
    if (ui->artikul_notebook->text().isEmpty()) {
        ui->artikul_notebook->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_notebook->setStyleSheet("background-color: white");
    }
    if (ui->number_notebook->text().isEmpty()) {
        ui->number_notebook->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_notebook->setStyleSheet("background-color: white");
    }
    if (ui->cost_notebook->text().isEmpty()) {
        ui->cost_notebook->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_notebook->setStyleSheet("background-color: white");
    }
    if (ui->memory->text().isEmpty()) {
        ui->memory->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->memory->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        QString artikul = ui->artikul_notebook->text();
        QString number = ui->number_notebook->text();
        QString cost = ui->cost_notebook->text();
        QString firma = ui->firma_notebook->currentText();
        QString memory_size = ui->memory->text();
        QString rasrad = ui->rasrad->currentText();
        QString architecture = ui->architecture->currentText();
        notebook* new_notebook = new notebook(artikul, number, cost, firma, memory_size, rasrad, architecture);

        current_shop->ware->add_notebook();
        current_shop->ware->add_node(new_notebook);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_notebook->clear();
        ui->number_notebook->clear();
        ui->cost_notebook->clear();
        ui->memory->clear();

        isModicate = true;
    }
}

void MainWindow::on_add_smartphone_clicked()
{
    bool correct_data = true;
    if (ui->artikul_smartphone->text().isEmpty()) {
        ui->artikul_smartphone->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_smartphone->setStyleSheet("background-color: white");
    }
    if (ui->number_smartphone->text().isEmpty()) {
        ui->number_smartphone->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_smartphone->setStyleSheet("background-color: white");
    }
    if (ui->cost_smartphone->text().isEmpty()) {
        ui->cost_smartphone->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_smartphone->setStyleSheet("background-color: white");
    }
    if (ui->screen_size_sm->text().isEmpty()) {
        ui->screen_size_sm->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->screen_size_sm->setStyleSheet("background-color: white");
    }
    if (ui->hours_working->text().isEmpty()) {
        ui->hours_working->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->hours_working->setStyleSheet("background-color: white");
    }
    if (ui->year_production->text().isEmpty()) {
        ui->year_production->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->year_production->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        QString artikul = ui->artikul_smartphone->text();
        QString number = ui->number_smartphone->text();
        QString cost = ui->cost_smartphone->text();
        QString firma = ui->firma_smartphone->currentText();
        QString screen_size = ui->screen_size_sm->text();
        QString hours_working = ui->hours_working->text();
        QString year = ui->year_production->text();
        smartphone* new_smartphone = new smartphone(artikul, number, cost, firma, screen_size, hours_working, year);

        current_shop->ware->add_smartphone();
        current_shop->ware->add_node(new_smartphone);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_smartphone->clear();
        ui->number_smartphone->clear();
        ui->cost_smartphone->clear();
        ui->screen_size_sm->clear();
        ui->hours_working->clear();
        ui->year_production->clear();

        isModicate = true;
    }
}

void MainWindow::on_add_tv_clicked()
{
    bool correct_data = true;
    if (ui->artikul_tv->text().isEmpty()) {
        ui->artikul_tv->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_tv->setStyleSheet("background-color: white");
    }
    if (ui->number_tv->text().isEmpty()) {
        ui->number_tv->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_tv->setStyleSheet("background-color: white");
    }
    if (ui->cost_tv->text().isEmpty()) {
        ui->cost_tv->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_tv->setStyleSheet("background-color: white");
    }
    if (ui->screen_size->text().isEmpty()) {
        ui->screen_size->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->screen_size->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        QString artikul = ui->artikul_tv->text();
        QString number = ui->number_tv->text();
        QString cost = ui->cost_tv->text();
        QString firma = ui->firma_tv->currentText();
        QString screen_size = ui->screen_size->text();
        QString internet;
        if (ui->internet_connect->isChecked()) {
            internet = "available";
        }
        else {
            internet = "don't available";
        }
        QString channels = ui->number_chanels->text();
        tv* new_tv = new tv(artikul, number, cost, firma, screen_size, internet, channels);

        current_shop->ware->add_tv();
        current_shop->ware->add_node(new_tv);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_tv->clear();
        ui->number_tv->clear();
        ui->cost_tv->clear();
        ui->screen_size->clear();
        ui->internet_connect->clearFocus();
        ui->number_chanels->clear();

        isModicate = true;
    }
}


void MainWindow::on_edit_product_clicked()
{
    if (ui->table_notebooks->rowCount() == 0 && ui->table_smartphones->rowCount() == 0 && ui->table_tvs->rowCount() == 0) {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_notebooks->currentRow() == -1 && ui->table_smartphones->currentRow() == -1 && ui->table_tvs->currentRow() == -1) {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
        else {
            int row_notebook = ui->table_notebooks->currentRow();
            int row_smartphone = ui->table_smartphones->currentRow();
            int row_tv = ui->table_tvs->currentRow();
            int id_product = 0;
            if (row_notebook != -1) {
                QTableWidgetItem *curitem = ui->table_notebooks->item(row_notebook, 0);
                ui->menu->setCurrentIndex(6);
                id_product = curitem->text().toInt();
                product* edit_product = current_shop->ware->find_node(id_product);
                ui->artikul_notebook_2->setText(edit_product->get_iid());
                ui->number_notebook_2->setText(edit_product->get_number());
                ui->cost_notebook_2->setText(edit_product->get_cost());
                ui->firma_notebook_2->setCurrentText(edit_product->get_firma());
                ui->memory_2->setText(edit_product->get_first());
                ui->rasrad_2->setCurrentText(edit_product->get_second());
                ui->architecture_2->setCurrentText(edit_product->get_third());
            }
            if (row_smartphone != -1) {
                QTableWidgetItem *curitem = ui->table_smartphones->item(row_smartphone, 0);
                ui->menu->setCurrentIndex(7);
                id_product = curitem->text().toInt();
                product* edit_product = current_shop->ware->find_node(id_product);
                ui->artikul_smartphone_2->setText(edit_product->get_iid());
                ui->number_smartphone_2->setText(edit_product->get_number());
                ui->cost_smartphone_2->setText(edit_product->get_cost());
                ui->firma_smartphone_2->setCurrentText(edit_product->get_firma());
                ui->screen_size_sm_2->setText(edit_product->get_first());
                ui->hours_working_2->setText(edit_product->get_second());
                ui->year_production_2->setText(edit_product->get_third());
            }
            if (row_tv != -1) {
                QTableWidgetItem *curitem = ui->table_tvs->item(row_tv, 0);
                ui->menu->setCurrentIndex(8);
                id_product = curitem->text().toInt();
                product* edit_product = current_shop->ware->find_node(id_product);
                ui->artikul_tv_2->setText(edit_product->get_iid());
                ui->number_tv_2->setText(edit_product->get_number());
                ui->cost_tv_2->setText(edit_product->get_cost());
                ui->firma_tv_2->setCurrentText(edit_product->get_firma());
                ui->screen_size_2->setText(edit_product->get_first());
                if (edit_product->get_second() == "available") {
                    ui->internet_connect_2->setChecked(true);
                }
                else {
                    ui->internet_connect_2->setChecked(false);
                }
                ui->number_chanels_2->setText(edit_product->get_third());
            }
        }
    }
}

void MainWindow::on_cancel_notebook_2_clicked()
{
    ui->menu->setCurrentIndex(0);
    ui->table_notebooks->clearSelection();
    ui->table_smartphones->clearSelection();
    ui->table_tvs->clearSelection();

    ui->artikul_notebook_2->clear();
    ui->number_notebook_2->clear();
    ui->cost_notebook_2->clear();
    ui->memory_2->clear();
    ui->table_notebooks->clearSelection();
}

void MainWindow::on_cancel_smartphone_2_clicked()
{
     ui->menu->setCurrentIndex(0);
     ui->table_notebooks->clearSelection();
     ui->table_smartphones->clearSelection();
     ui->table_tvs->clearSelection();

     ui->artikul_smartphone_2->clear();
     ui->number_smartphone_2->clear();
     ui->cost_smartphone_2->clear();
     ui->screen_size_sm_2->clear();
     ui->hours_working_2->clear();
     ui->year_production_2->clear();
     ui->table_smartphones->clearSelection();
}

void MainWindow::on_cancel_tv_2_clicked()
{
     ui->menu->setCurrentIndex(0);
     ui->table_notebooks->clearSelection();
     ui->table_smartphones->clearSelection();
     ui->table_tvs->clearSelection();

     ui->artikul_tv_2->clear();
     ui->number_tv_2->clear();
     ui->cost_tv_2->clear();
     ui->screen_size_2->clear();
     ui->internet_connect_2->clearFocus();
     ui->number_chanels_2->clear();
     ui->table_tvs->clearSelection();
}

void MainWindow::on_change_notebook_clicked()
{
    bool correct_data = true;
    if (ui->artikul_notebook_2->text().isEmpty()) {
        ui->artikul_notebook_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_notebook_2->setStyleSheet("background-color: white");
    }
    if (ui->number_notebook_2->text().isEmpty()) {
        ui->number_notebook_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_notebook_2->setStyleSheet("background-color: white");
    }
    if (ui->cost_notebook_2->text().isEmpty()) {
        ui->cost_notebook_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_notebook_2->setStyleSheet("background-color: white");
    }
    if (ui->memory_2->text().isEmpty()) {
        ui->memory_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->memory_2->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        int row_notebook = ui->table_notebooks->currentRow();
        QTableWidgetItem *curitem = ui->table_notebooks->item(row_notebook, 0);
        int id_product = curitem->text().toInt();

        QString artikul = ui->artikul_notebook_2->text();
        QString number = ui->number_notebook_2->text();
        QString cost = ui->cost_notebook_2->text();
        QString firma = ui->firma_notebook_2->currentText();
        QString memory_size = ui->memory_2->text();
        QString rasrad = ui->rasrad_2->currentText();
        QString architecture = ui->architecture_2->currentText();

        product* edit_notebook = current_shop->ware->find_node(id_product);
        edit_notebook->set_data_product(artikul, number, cost, firma, memory_size, rasrad, architecture);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_notebook_2->clear();
        ui->number_notebook_2->clear();
        ui->cost_notebook_2->clear();
        ui->memory_2->clear();

        ui->table_notebooks->clearSelection();
        ui->table_smartphones->clearSelection();
        ui->table_tvs->clearSelection();

        isModicate = true;
    }
}

void MainWindow::on_change_smartphone_clicked()
{
    bool correct_data = true;
    if (ui->artikul_smartphone_2->text().isEmpty()) {
        ui->artikul_smartphone_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_smartphone_2->setStyleSheet("background-color: white");
    }
    if (ui->number_smartphone_2->text().isEmpty()) {
        ui->number_smartphone_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_smartphone_2->setStyleSheet("background-color: white");
    }
    if (ui->cost_smartphone_2->text().isEmpty()) {
        ui->cost_smartphone_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_smartphone_2->setStyleSheet("background-color: white");
    }
    if (ui->screen_size_sm_2->text().isEmpty()) {
        ui->screen_size_sm_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->screen_size_sm_2->setStyleSheet("background-color: white");
    }
    if (ui->hours_working_2->text().isEmpty()) {
        ui->hours_working_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->hours_working_2->setStyleSheet("background-color: white");
    }
    if (ui->year_production_2->text().isEmpty()) {
        ui->year_production_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->year_production->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        int row_smartphone = ui->table_smartphones->currentRow();
        QTableWidgetItem *curitem = ui->table_smartphones->item(row_smartphone, 0);
        int id_product = curitem->text().toInt();

        QString artikul = ui->artikul_smartphone_2->text();
        QString number = ui->number_smartphone_2->text();
        QString cost = ui->cost_smartphone_2->text();
        QString firma = ui->firma_smartphone_2->currentText();
        QString screen_size = ui->screen_size_sm_2->text();
        QString hours_working = ui->hours_working_2->text();
        QString year = ui->year_production_2->text();

        product* new_smartphone = current_shop->ware->find_node(id_product);
        new_smartphone->set_data_product(artikul, number, cost, firma, screen_size, hours_working, year);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_smartphone_2->clear();
        ui->number_smartphone_2->clear();
        ui->cost_smartphone_2->clear();
        ui->screen_size_sm_2->clear();
        ui->hours_working_2->clear();
        ui->year_production_2->clear();

        ui->table_notebooks->clearSelection();
        ui->table_smartphones->clearSelection();
        ui->table_tvs->clearSelection();

        isModicate = true;
    }
}

void MainWindow::on_change_tv_clicked()
{
    bool correct_data = true;
    if (ui->artikul_tv_2->text().isEmpty()) {
        ui->artikul_tv_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->artikul_tv_2->setStyleSheet("background-color: white");
    }
    if (ui->number_tv_2->text().isEmpty()) {
        ui->number_tv_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->number_tv_2->setStyleSheet("background-color: white");
    }
    if (ui->cost_tv_2->text().isEmpty()) {
        ui->cost_tv_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->cost_tv_2->setStyleSheet("background-color: white");
    }
    if (ui->screen_size_2->text().isEmpty()) {
        ui->screen_size_2->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->screen_size_2->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        int row_tv = ui->table_tvs->currentRow();
        QTableWidgetItem *curitem = ui->table_tvs->item(row_tv, 0);
        int id_product = curitem->text().toInt();

        QString artikul = ui->artikul_tv_2->text();
        QString number = ui->number_tv_2->text();
        QString cost = ui->cost_tv_2->text();
        QString firma = ui->firma_tv_2->currentText();
        QString screen_size = ui->screen_size_2->text();
        QString internet;
        if (ui->internet_connect_2->isChecked()) {
            internet = "available";
        }
        else {
            internet = "don't available";
        }
        QString channels = ui->number_chanels_2->text();

        product* new_tv = current_shop->ware->find_node(id_product);
        new_tv->set_data_product(artikul, number, cost, firma, screen_size, internet, channels);

        update_table();
        ui->menu->setCurrentIndex(0);
        ui->artikul_tv_2->clear();
        ui->number_tv_2->clear();
        ui->cost_tv_2->clear();
        ui->screen_size_2->clear();
        ui->internet_connect_2->clearFocus();
        ui->number_chanels_2->clear();

        ui->table_notebooks->clearSelection();
        ui->table_smartphones->clearSelection();
        ui->table_tvs->clearSelection();

        isModicate = true;
    }
}

void MainWindow::on_cancel_clicked()
{
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_delete_product_clicked()
{
    if (ui->table_notebooks->rowCount() == 0 && ui->table_smartphones->rowCount() == 0 && ui->table_tvs->rowCount() == 0) {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_notebooks->currentRow() == -1 && ui->table_smartphones->currentRow() == -1 && ui->table_tvs->currentRow() == -1) {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
        else {
            int row_notebook = ui->table_notebooks->currentRow();
            int row_smartphone = ui->table_smartphones->currentRow();
            int row_tv = ui->table_tvs->currentRow();
            int id_product = 0;
            if (row_notebook != -1) {
                QTableWidgetItem *curitem = ui->table_notebooks->item(row_notebook, 0);
                id_product = curitem->text().toInt();
                current_shop->ware->delete_node(id_product);
            }
            if (row_smartphone != -1) {
                QTableWidgetItem *curitem = ui->table_smartphones->item(row_smartphone, 0);
                id_product = curitem->text().toInt();
                current_shop->ware->delete_node(id_product);
            }
            if (row_tv != -1) {
                QTableWidgetItem *curitem = ui->table_tvs->item(row_tv, 0);
                id_product = curitem->text().toInt();
                current_shop->ware->delete_node(id_product);
            }
        }
        ui->menu->setCurrentIndex(0);
        ui->table_notebooks->clearSelection();
        ui->table_smartphones->clearSelection();
        ui->table_tvs->clearSelection();

        update_table();
    }
}

void MainWindow::on_change_shop_clicked()
{
    ui->menu->setCurrentIndex(9);
    update_table_shops();

}

void MainWindow::on_stay_shop_clicked()
{
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_cancel_new_shop_clicked()
{
    ui->menu->setCurrentIndex(0);
}

void MainWindow::on_add_shop_clicked()
{
    ui->menu->setCurrentIndex(10);
}

void MainWindow::on_add_new_shop_clicked()
{
    bool correct_data = true;
    if (ui->name_shop->text().isEmpty()) {
        ui->name_shop->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->name_shop->setStyleSheet("background-color: white");
    }
    if (ui->phone_shop->text().isEmpty()) {
        ui->phone_shop->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->phone_shop->setStyleSheet("background-color: white");
    }
    if (ui->adress_shop->text().isEmpty()) {
        ui->adress_shop->setStyleSheet("background-color: red");
        correct_data = false;
    }
    else {
        ui->adress_shop->setStyleSheet("background-color: white");
    }
    if (correct_data == true) {
        QString name = ui->name_shop->text();
        QString phone = ui->phone_shop->text();
        QString adress = ui->adress_shop->text();
        current_shop_artikul++;
        shop* new_shop = new shop(name, adress, phone, nullptr, current_shop_artikul);

        shops->add_node(new_shop);
        current_shop = new_shop;
        update_table();
        update_table_shops();
        ui->menu->setCurrentIndex(0);

        ui->name_shop->clear();
        ui->phone_shop->clear();
        ui->adress_shop->clear();

        isModicate = true;
    }
}

void MainWindow::on_choose_new_shop_2_clicked()
{
    if (ui->table_shops->rowCount() == 0) {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_shops->currentRow() == -1) {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
        else {
            int row_shop = ui->table_shops->currentRow();
            QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0);
            int id_shop = curitem->text().toInt();
            current_shop = shops->find_node(id_shop);
            update_table();
            ui->menu->setCurrentIndex(0);
        }
    }
}

void MainWindow::on_delete_shop_clicked()
{
    if (ui->table_shops->rowCount() == 0) {
        QMessageBox::critical(this, "Error", "Table is empty!");
    }
    else {
        if (ui->table_shops->currentRow() == -1) {
            QMessageBox::critical(this, "Error", "No line is selected!");
        }
        else {
            int row_shop = ui->table_shops->currentRow();
            QTableWidgetItem *curitem = ui->table_shops->item(row_shop, 0);
            int id_shop = curitem->text().toInt();
            shops->delete_node(id_shop);
            update_table();
            update_table_shops();
            ui->menu->setCurrentIndex(0);

            isModicate = true;
        }
    }
}

void MainWindow::new_file() {
    if (isModicate == true) {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();
        if(res == QMessageBox::Yes) {
            save_file();
        }
    }
    shops->clear_list();
    current_shop->ware->clear_list();
    shops->add_node(current_shop);
    update_table();
    update_table_shops();
    isModicate = false;
}

void MainWindow::save_file() {
    QFile file;

    if(current_file == "")
    {
        save_as();
    }
    else
    {
        file.setFileName(current_file);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        write_in_file(file);
        isModicate = false;
        file.close();
    }
}

void MainWindow::write_in_file(QFile &file) {
    QTextStream stream(&file);
    stream.setCodec("UTF-8");

    stream << shops->get_count_all_shops() << endl;
    shop* write_current_shop = shops->get_head();
    while (write_current_shop != nullptr) {
        list_product* write_current_products = write_current_shop->get_ware();
        stream << write_current_products->get_count() << endl;
        product* write_current_product = write_current_products->get_head();
        while (write_current_product != nullptr) {
            stream << write_current_product->get_category() << endl;
            stream << write_current_product->get_iid() << endl;
            stream << write_current_product->get_number() << endl;
            stream << write_current_product->get_cost() << endl;
            stream << write_current_product->get_firma() << endl;
            stream << write_current_product->get_first() << endl;
            stream << write_current_product->get_second() << endl;
            stream << write_current_product->get_third() << endl;
            write_current_product = write_current_product->next;
        }
        write_current_shop = write_current_shop->get_next();
    }
}

void MainWindow::save_as() {
    QFile file;

    QString fileName = QFileDialog::getSaveFileName(this, "Save as ...", QDir::homePath(), "Text file (*.txt)");
    if (!fileName.isEmpty())
    {
        current_file = fileName;
        file.setFileName(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        write_in_file(file);
        isModicate = false;
        file.close();
    }
}

void MainWindow::exit_prog() {
    if (isModicate == true) {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            save_file();
        }
    }

    close();
}

void MainWindow::about_program() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("The program by Svetlana Rudneva\nAll roots reserved");
    msgBox.exec();
}

void MainWindow::help() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("How use this app");
    msgBox.setText("This program is very easy in using!\nYou will get success!\nWe belive that you will enjoy!");
    msgBox.exec();
}

void MainWindow::open_file() {
    if (isModicate == true) {
        QMessageBox msgBox;
        msgBox.setText("Save changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int res = msgBox.exec();

        if(res == QMessageBox::Yes)
        {
            save_file();
        }
    }
    shops->clear_list();
    current_shop->ware->clear_list();
    update_table();
    update_table_shops();
    isModicate = false;

    QString fileName = QFileDialog::getOpenFileName(this, "Open file", QDir::homePath(), "Text file (*.txt)");

    qDebug() << "";

    if(!fileName.isEmpty())
    {
        current_file = fileName;

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        int count_shops = (stream.readLine()).toInt();

        for(int i = 0; i < count_shops; i++) {
            int count_products = (stream.readLine()).toInt();
            shop* current = new shop();
            for (int j = 0; j < count_products; j++) {
                QString category = stream.readLine();
                QString iid = stream.readLine();
                QString number = stream.readLine();
                QString cost = stream.readLine();
                QString firma = stream.readLine();
                if (category == "Notebook") {
                    QString memory_size = stream.readLine();
                    QString rasrad = stream.readLine();
                    QString architecture = stream.readLine();
                    product* new_product = new notebook(iid, number, cost, firma, memory_size, rasrad, architecture);
                    current->ware->add_node(new_product);
                    current->ware->add_notebook();
                }
                if (category == "Smartphone") {
                    QString screen_size = stream.readLine();
                    QString hours_working = stream.readLine();
                    QString year_production = stream.readLine();
                    product* new_product = new smartphone(iid, number, cost, firma, screen_size, hours_working, year_production);
                    current->ware->add_node(new_product);
                    current->ware->add_smartphone();
                }
                if (category == "TV") {
                    QString screen_size = stream.readLine();
                    QString internet_connect = stream.readLine();
                    QString number_channels = stream.readLine();
                    product* new_product = new tv(iid, number, cost, firma, screen_size, internet_connect, number_channels);
                    current->ware->add_node(new_product);
                    current->ware->add_tv();
                }
            }
            shops->add_node(current);
            current_shop = current;
        }

        file.close();

        update_table();
        update_table_shops();
        isModicate = false;
    }
}
