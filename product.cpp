#include "product.h"

product::product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_category, product* m_next, int m_current): // конструктор
    next(m_next), category(m_category), iid(m_iid), number(m_number), cost(m_cost), firma(m_firma), current(m_current)
{
    current = number_products;
    number_products++;
}

// получение данных из приватных полей
QString product::get_iid() { return iid; }
QString product::get_number() { return number; }
QString product::get_cost() { return cost; }
QString product::get_firma() { return firma; }
product* product::get_next() { return next; }
QString product::get_category() { return category; }
int product::get_current() { return current; }

// установка новых данных в приватные поля
void product::set_iid(QString m_iid) { iid = m_iid; }
void product::set_number(QString m_number) { number = m_number; }
void product::set_cost(QString m_cost) { cost = m_cost; }
void product::set_firma(QString m_firma) { firma = m_firma; }
void product::set_next(product* m_next) { next = m_next; }
void product::set_category(QString m_category) { category = m_category; }

void product::set_data_product_main(QString m_iid, QString m_number, QString m_cost, QString m_firma) { // установка данных о продукте
    iid = m_iid;
    number = m_number;
    cost = m_cost;
    firma = m_firma;
}


notebook::notebook(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_memory_size, QString m_rasrad, QString m_arch): // конструктор
    product(m_iid, m_number, m_cost, m_firma, "Notebook", nullptr, 0), memory_size(m_memory_size), rasrad(m_rasrad), arch(m_arch)
{ number_notebooks++; }

QString notebook::get_first() { return memory_size; }
QString notebook::get_second() { return rasrad; }
QString notebook::get_third() { return arch; }

void notebook::set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_memory_size, QString m_rasrad, QString m_arch) { // установка данных о товаре
    product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
    memory_size = m_memory_size;
    rasrad = m_rasrad;
    arch = m_arch;
}

smartphone::smartphone(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_hours_working, QString m_year_production): // конструктор
    product(m_iid, m_number, m_cost, m_firma, "Smartphone", nullptr, 0), screen_size(m_screen_size), hours_working(m_hours_working), year_production(m_year_production)
{ number_smartphones++; }

QString smartphone::get_first() { return screen_size; }
QString smartphone::get_second() { return hours_working; }
QString smartphone::get_third() { return year_production; }

void smartphone::set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_hours_working, QString m_year_production) {
    product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
    screen_size = m_screen_size;
    hours_working = m_hours_working;
    year_production = m_year_production;
}

tv::tv(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_internet_connect, QString m_number_channels): // конструктор
    product(m_iid, m_number, m_cost, m_firma, "TV", nullptr, 0), screen_size(m_screen_size), internet_connect(m_internet_connect), number_channels(m_number_channels)
{ number_tvs++; }

QString tv::get_first() { return screen_size; }
QString tv::get_second() { return internet_connect; }
QString tv::get_third() { return number_channels; }

void tv::set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_internet_connect, QString m_number_channels) { // установка данных
    product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
    screen_size = m_screen_size;
    internet_connect = m_internet_connect;
    number_channels = m_number_channels;
}

product* list_product::Prev(product* node) { // переход к предыдущему узлу
    if (node == nullptr) { return nullptr; }
    if (node == head) { return nullptr; }
    product *p = head;
    while (p->next != node) {
        p = p->next;
    }
    return p;
}

list_product::list_product(product* m_head, int m_count, int m_count_notebooks, int m_count_smartphones, int m_count_tvs): // конструктор
    head(m_head), count(m_count), count_notebooks(m_count_notebooks), count_smartphones(m_count_smartphones), count_tvs(m_count_tvs)
{
    count = 0;
    head = nullptr;
}

void list_product::clear_list() {
    product* current = head;
    while (current != nullptr) {
        product* current_tmp = current->next;
        delete current;
        current = current_tmp;
        delete current_tmp;
    }
    delete current;
    head = nullptr;
    count_notebooks = 0;
    count_smartphones = 0;
    count_tvs = 0;
    count = 0;
}

int list_product::get_count() { return count; }
int list_product::get_count_notebooks() { return count_notebooks; }
int list_product::get_count_smartphones() { return count_smartphones; }
int list_product::get_count_tvs() { return count_tvs; }
product* list_product::get_head() { return head; }

product* list_product::Follow(product* node) { // переход к следующему узлу
    if (node == nullptr) { return nullptr; }
    return node->next;
}

product* list_product::Last_node() { // переход к последнему узлу
    product* p = head;
    while (Follow(p) != nullptr) { p = Follow(p); }
    return p;
}

void list_product::delete_node(int id_product) {
    product* current_product = head;
    while (current_product != nullptr) {
        if (current_product->get_current() == id_product) {
            if (current_product->get_category() == "Notebook") { count_notebooks--; }
            else {
                if (current_product->get_category() == "Smartphone") { count_smartphones--; }
                else { count_tvs--; }
            }
            count--;
            if (current_product == head) {
                head = current_product->next;
                delete current_product;
                break;
            }
            else {
                product* prev = Prev(current_product);
                prev->next = (current_product->next);
                delete current_product;
                break;
            }
        }
        current_product = current_product->get_next();
    }
}

void list_product::add_node(product* new_node) {
    if (head == nullptr) {
        head = new_node;
    }
    else {
        new_node->next = head;
        head = new_node;
    }
    count++;
    if (new_node->get_category() == "Notebook") { count_notebooks++; }
    if (new_node->get_category() == "Smartphone") { count_smartphones++; }
    if (new_node->get_category() == "TV") { count_tvs++; }
}

product* list_product::find_node(int id_product) {
    product* current = head;
    while (current != nullptr && current->get_current() != id_product) {
        current = current->next;
    }
    return current;
}
