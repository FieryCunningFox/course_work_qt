#ifndef SHOP_H
#define SHOP_H

#include "product.h"

#include <QString>

class shop
{
private:
    shop* next;
    int artikul;
    QString name_shop;
    QString adress;
    QString phone;
    list_product* ware;

    static int number_shop;

public:
    shop(QString m_name_shop="RE_store", QString m_adress="London, Baker str. 221B", QString m_phone = "89203345678", list_product* m_ware = nullptr, int m_artikul = 1);

    int get_artikul();
    QString get_name_shop();
    QString get_adress();
    QString get_phone();
    shop* get_next();
    list_product* get_ware();

    static int get_number_shop() { return number_shop; }

    void set_data_shop(QString m_name_shop, QString m_adress, QString m_phone) ;

    void set_name(QString name);
    void set_adress(QString m_adress);
    void set_phone(QString m_phone);
    void set_next(shop* m_next);

    friend class shop_list;
    friend class MainWindow;
};


class shop_list
{
private:
    shop* head; // указатель на начало

    static int count_all_shops;

    shop* Prev(shop* node); // переход к предыдущему узлу

public:
    shop_list();

    ~shop_list() { // деструктор
        shop* r;
        while (head) {
            r = head;
            head = head->next;
            delete r;
        }
    }

    shop* get_head();
    static int get_count_all_shops() { return count_all_shops; }

    shop* Follow(shop* node); // переход к следующему узлу

    shop* find_node(int id_shop);

    void add_node(shop* new_shop); // добавление нового магазина в сеть

    void delete_node(int id_shop);

    void clear_list();
};

#endif // SHOP_H
