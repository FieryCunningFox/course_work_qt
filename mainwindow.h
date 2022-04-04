#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QDate>

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

    void on_add_new_clicked();

    void on_notebook_clicked();

    void on_smartphone_clicked();

    void on_tv_clicked();

    void on_cancel_tv_clicked();

    void on_cancel_notebook_clicked();

    void on_cancel_smartphone_clicked();

    void on_add_notebook_clicked();

    void on_add_smartphone_clicked();

    void on_add_tv_clicked();

    void on_edit_product_clicked();

    void on_cancel_notebook_2_clicked();

    void on_cancel_smartphone_2_clicked();

    void on_cancel_tv_2_clicked();

    void on_change_notebook_clicked();

    void on_change_smartphone_clicked();

    void on_change_tv_clicked();

    void on_cancel_clicked();

    void on_delete_product_clicked();

    void on_change_shop_clicked();

    void on_stay_shop_clicked();

    void on_cancel_new_shop_clicked();

    void on_add_shop_clicked();

    void on_add_new_shop_clicked();

    void on_choose_new_shop_2_clicked();

    void on_delete_shop_clicked();

    // функции меню
    void new_file();
    void open_file();
    void save_file();
    void save_as();
    void exit_prog();
    void help();
    void about_program();


    void on_cancel_new_shop_2_clicked();

    void on_edit_shop_done_clicked();

    void on_edit_shop_data_clicked();

private:
    Ui::MainWindow *ui;

    shop_list* shops;
    int current_shop_artikul;
    shop* current_shop;

    bool isModicate;
    QString current_file;

    void update_table();
    void update_table_shops();

    void write_in_file(QFile &file);
};
#endif // MAINWINDOW_H
