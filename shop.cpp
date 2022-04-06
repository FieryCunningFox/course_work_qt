#include "shop.h"


shop::shop(QString m_name_shop, QString m_adress, QString m_phone, list_product* m_ware, int m_artikul):
    artikul(m_artikul), name_shop(m_name_shop), adress(m_adress), phone(m_phone), ware(m_ware)
{
    ware = new list_product();
    number_shop++;
};

int shop::get_artikul() { return artikul; }
QString shop::get_name_shop() { return name_shop; }
QString shop::get_adress() { return adress; }
QString shop::get_phone() { return phone; }
shop* shop::get_next() { return next; }
list_product* shop::get_ware() { return ware; };

void shop::set_data_shop(QString m_name_shop, QString m_adress, QString m_phone) {
    name_shop = m_name_shop;
    adress = m_adress;
    phone = m_phone;
}

void shop::set_name(QString name) { name_shop = name; }
void shop::set_adress(QString m_adress) { adress = m_adress; }
void shop::set_phone(QString m_phone) { phone = m_phone; }
void shop::set_next(shop* m_next) { next = m_next; }


shop_list::shop_list() { head = nullptr; } // конструктор

shop* shop_list::get_head() { return head; }

shop* shop_list::Follow(shop* node) { // переход к следующему узлу
    if (node == nullptr) { return nullptr; }
    return node->next;
}

void shop_list::add_node(shop* new_shop) { // добавление нового магазина в сеть
    if (head == nullptr) {
        head = new_shop;
    }
    else {
        shop* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_shop;
    }
    count_all_shops++;
}

shop* shop_list::Prev(shop* node) {
    if (node == nullptr) { return nullptr; }
    if (node == head) { return nullptr; }
    shop *p = head;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}

void shop_list::delete_node(int id_shop) {
    shop* current_shop = head;
    while (current_shop != nullptr) {
        if (current_shop->get_artikul() == id_shop) {
            count_all_shops--;
            if (current_shop == head) {
                head = current_shop->next;
                delete current_shop;
                break;
            }
            else {
                shop* prev = Prev(current_shop);
                prev->next = (current_shop->next);
                delete current_shop;
                break;
            }
        }
        current_shop = current_shop->get_next();
    }
}

shop* shop_list::find_node(int id_shop) {
    shop* current = head;
    while (current != nullptr && current->get_artikul() != id_shop) {
        current = current->next;
    }
    return current;
}

void shop_list::clear_list() {
    head = nullptr;
    count_all_shops = 0;
}
