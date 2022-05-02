#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QDate>
#include <QMenu>
#include <QMenuBar>


#include "product.h"
#include "shop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, int m_current_shop_artikul = 1, shop_list* m_shops = nullptr, shop* m_current_shop = nullptr, bool m_isModificate = false, QString m_current_file = "");
    ~MainWindow();

private slots:

    void on_add_new_clicked(); // добавление нового продукта - переход в меню выбора типа продукта

    void on_notebook_clicked(); // выбор типа продукта - ноутбук

    void on_smartphone_clicked(); // выбор типа продукта - смартфон

    void on_tv_clicked(); // выбор типа продукта - телевизор

    void on_cancel_tv_clicked(); // отмена добавление телевизора

    void on_cancel_notebook_clicked(); // отмена добавления ноутбука

    void on_cancel_smartphone_clicked(); // отмена добавления смартфона

    void on_add_notebook_clicked(); // добавление ноутбука

    void on_add_smartphone_clicked(); // добавление смартфона

    void on_add_tv_clicked(); // добавление телевизора

    void on_edit_product_clicked(); // редактирование продукта

    void on_cancel_notebook_2_clicked(); // отмена редактирования ноутбука

    void on_cancel_smartphone_2_clicked(); // отмена редактирования смартфона

    void on_cancel_tv_2_clicked(); // отмена редактирования телевизора

    void on_change_notebook_clicked(); // редактирование ноутбука

    void on_change_smartphone_clicked(); // редактирование смартфона

    void on_change_tv_clicked(); // редактирование телевизора

    void on_cancel_clicked(); // отмена добавления

    void on_delete_product_clicked(); // удаление продукта

    void on_change_shop_clicked(); // смена текущего магазина - список магазинов, возможность удалить, отредактировать данные магазина, а аткже добавить новый

    void on_stay_shop_clicked(); // отмена изменения текущего магазина

    void on_cancel_new_shop_clicked(); // отмена добавления нового магазина

    void on_add_shop_clicked(); // добавление нового магазина - открытие формы для записи данных

    void on_add_new_shop_clicked(); // добавление нового магазина

    void on_choose_new_shop_2_clicked(); // выбор нового магазина в качестве текущего

    void on_delete_shop_clicked(); // удаление магазина

    // функции меню
    void new_file(); // новый файл
    void open_file(); // открытие файла
    void save_file(); // быстрое сохранение
    void save_as(); // сохранение под новым именем
    void exit_prog(); // выход из программы
    void help(); // справка
    void about_program(); // немного о программе

    void on_cancel_new_shop_2_clicked(); // отмена добавления нового магазина

    void on_edit_shop_done_clicked(); // завершение редактирования магазина - изменения данных

    void on_edit_shop_data_clicked(); // изменение данных магазина

    void on_search_product_clicked(); // поиск продуктов по определенным критериям

    void on_cancel_search_clicked(); // отмена поиска

    void on_search_by_cost_clicked(); // поиск по стоимости

    void on_search_cost_product_clicked(); // завершено введение данных для поиска - старт поиска

    void on_cancel_search_2_clicked(); // отмена поиска

    void on_search_firm_product_clicked(); // поиск по фирме

    void on_search_by_firm_clicked(); // завершение введения данных для поиска - старт поиска

    void on_edit_notebook_2_clicked();

    void on_editsmartphone_clicked();

    void on_edit_tv_2_clicked();

    void on_cancel_edit_clicked();

    void on_delete_notebook_clicked();

    void on_delete_smartphone_clicked();

    void on_delete_tv_clicked();

    void on_cancel_delete_clicked();

    void on_cancel_search_3_clicked();

private:
    Ui::MainWindow *ui;

    shop_list* shops; // список всех магазинов сети
    int current_shop_artikul; // артикул текущего магазина - для удобства поиска в общем списке
    shop* current_shop; // текущий магазин

    bool isModicate; // флаг изменения данных - для выдачи предупреждения о несохраненных данных
    QString current_file; // имя текущего файла

    void update_table(); // обновление таблицы с продуктами текущего магазина
    void update_table_shops(); // обновление таблицы с магазинами

    void write_in_file(QFile &file); // запись в файл
};
#endif // MAINWINDOW_H
