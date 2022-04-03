#include "mainwindow.h"

#include <QApplication>

int product::number_products = 0;
int shop_list::count_all_shops = 0;
int notebook::number_notebooks = 0;
int smartphone::number_smartphones = 0;
int tv::number_tvs = 0;
int shop::number_shop = 0;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
