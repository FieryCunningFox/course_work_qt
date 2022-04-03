#include "product.h"

product::product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_category, product* m_next, int m_current): // конструктор
    category(m_category), iid(m_iid), number(m_number), cost(m_cost), firma(m_firma), next(m_next), current(m_current)
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
{
    number_notebooks++;
}

QString notebook::get_memory_size() { return memory_size; }
QString notebook::get_rasrad() { return rasrad; }
QString notebook::get_arch() { return arch; }


smartphone::smartphone(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_hours_working, QString m_year_production): // конструктор
    product(m_iid, m_number, m_cost, m_firma, "Smartphone", nullptr, 0), screen_size(m_screen_size), hours_working(m_hours_working), year_production(m_year_production)
{
    number_smartphones++;
}

QString smartphone::get_screen_size() { return screen_size; }
QString smartphone::get_hours_working() { return hours_working; }
QString smartphone::get_year_production() { return year_production; }


tv::tv(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_internet_connect, QString m_number_channels): // конструктор
    product(m_iid, m_number, m_cost, m_firma, "TV", nullptr, 0), screen_size(m_screen_size), internet_connect(m_internet_connect), number_channels(m_number_channels) {}

// получение данных из приватных полей
QString tv::get_screen_size() { return screen_size; }
QString tv::get_internet_connect() { return internet_connect; }
QString tv::get_number_px() { return number_channels; }


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

void list_product::add_notebook() { count_notebooks++; }
void list_product::add_smartphone() { count_smartphones++; }
void list_product::add_tv() { count_tvs++; }

void list_product::set_head(product* m_head) { head = m_head; }


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
            if (current_product->get_category() == "Notebook") {
                count_notebooks--;
            }
            else {
                if (current_product->get_category() == "Smartphone") {
                    count_smartphones--;
                }
                else {
                    count_tvs--;
                }
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
        product* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    count++;
}

product* list_product::find_node(int id_product) {
    product* current = head;
    while (current != nullptr && current->get_current() != id_product) {
        current = current->next;
    }
    return current;
}
