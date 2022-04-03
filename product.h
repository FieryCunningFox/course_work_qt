#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class product
{
protected:
    product* next; // адрес следующего узла

private:
    QString category;
    QString iid;
    QString number;
    QString cost;
    QString firma;

    int current;

    static int number_products; // количество товаров во всей сети магазинов
public:
    product(QString m_iid = "0", QString m_number = "0", QString m_cost = "0", QString m_firma = "Intel", QString m_category = "Smartphone", product* m_next = nullptr, int m_current = 0); // конструктор

    virtual ~product() = default; // виртуальный деструктор

    // получение данных из приватных полей
    QString get_iid();
    QString get_number();
    QString get_cost();
    QString get_firma();
    product* get_next();
    QString get_category();
    int get_current();

    // установка новых данных в приватные поля
    void set_iid(QString m_iid);
    void set_number(QString m_number);
    void set_cost(QString m_cost);
    void set_firma(QString m_firma);
    void set_next(product* m_next);
    void set_category(QString m_category);

    static int get_number_products() { return number_products; } // получение данных об общем количестве товаров

    void set_data_product_main(QString m_iid, QString m_number, QString m_cost, QString m_firma); // установка данных о продукте

    virtual QString get_first() = 0;
    virtual QString get_second() = 0;
    virtual QString get_third() = 0;

    virtual void set_data_product(QString, QString, QString, QString, QString, QString, QString) = 0;

    friend class list_product;  // для того, чтобы в классе List было доступно поле next
    friend class MainWindow;
};


class notebook final: public product {
private:
    QString memory_size;
    QString rasrad;
    QString arch;

    static int number_notebooks; // количество ноутбуков по всей сети магазинов

public:
    notebook(QString m_iid = "0", QString m_number = "0", QString m_cost = "0", QString m_firma = "Intel", QString m_memory_size = "128", QString m_rasrad = "64", QString m_arch = "1"); // конструктор

     ~notebook() = default; // деструктор

    // получение данных из приватных полей
    QString get_memory_size();
    QString get_rasrad();
    QString get_arch();

    static int get_number_notebooks() { return number_notebooks; }

    void set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_memory_size, QString m_rasrad, QString m_arch) { // установка данных о товаре
        product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
        memory_size = m_memory_size;
        rasrad = m_rasrad;
        arch = m_arch;
    }

    QString get_first() { return memory_size; }
    QString get_second() { return rasrad; }
    QString get_third() { return arch; }
};


class smartphone final: public product {
private:
    QString screen_size;
    QString hours_working;
    QString year_production;

    static int number_smartphones;

public:
    smartphone(QString m_iid = "0", QString m_number = "0", QString m_cost = "0", QString m_firma = "Intel", QString m_screen_size = "5.1", QString m_hours_working = "17", QString m_year_production = "2022"); // конструктор

    ~smartphone() = default; // деструктор

    // получение данных из приватных полей
    QString get_screen_size();
    QString get_hours_working();
    QString get_year_production();

    static int get_number_smartphones() { return number_smartphones; }

    void set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_hours_working, QString m_year_production) {
        product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
        screen_size = m_screen_size;
        hours_working = m_hours_working;
        year_production = m_year_production;
    }

    QString get_first() { return screen_size; }
    QString get_second() { return hours_working; }
    QString get_third() { return year_production; }
};


class tv final: public product {
private:
    QString screen_size;
    QString internet_connect;
    QString number_channels;

    static int number_tvs;
public:
    tv(QString m_iid = "0", QString m_number = "0", QString m_cost = "0", QString m_firma = "Intel", QString m_screen_size = "50.6", QString m_internet_connect = "true", QString m_number_channels = "10000"); // конструктор

    ~tv() = default; // деструктор

    // получение данных из приватных полей
    QString get_screen_size();
    QString get_internet_connect();
    QString get_number_px();

    static int get_number_tvs() { return number_tvs; }

    void set_data_product(QString m_iid, QString m_number, QString m_cost, QString m_firma, QString m_screen_size, QString m_internet_connect, QString m_number_channels) { // установка данных
        product:: set_data_product_main(m_iid, m_number, m_cost, m_firma);
        screen_size = m_screen_size;
        internet_connect = m_internet_connect;
        number_channels = m_number_channels;
    }

    QString get_first() { return screen_size; }
    QString get_second() { return internet_connect; }
    QString get_third() { return number_channels; }
};


class list_product {
private:
    product* head; // указатель на начало
    int count; // количество узлов

    int count_notebooks;
    int count_smartphones;
    int count_tvs;

    product* Prev(product* node); // переход к предыдущему узлу

public:
    list_product(product* m_head = nullptr, int m_count = 0, int m_count_notebooks = 0, int m_count_smartphones = 0, int m_count_tvs = 0); // конструктор

    ~list_product() { // деструктор - очистка
        product *r;
        while (head)
        {
            r = head;
            head = head->next;
            delete r;
          }
    }

    void clear_list();

    int get_count();
    int get_count_notebooks();
    int get_count_smartphones();
    int get_count_tvs();
    product* get_head();

    void add_notebook();
    void add_smartphone();
    void add_tv();

    void set_head(product* m_head);

    product* Follow(product* node); // переход к следующему узлу

    product* Last_node(); // переход к последнему узлу

    void delete_node(int id_product);

    product* find_node(int id_product);

    void add_node(product* new_node);

    friend class MainWindow;
};

#endif // PRODUCT_H
