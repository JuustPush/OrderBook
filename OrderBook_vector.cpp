#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>


enum class OrderType {
    Buy,
    Sell
};


struct Order {
    double price;
    int volume;
    OrderType type;

    Order(double p, int v, OrderType t) : price(p), volume(v), type(t) {}
    bool operator==(const Order& other) const {
        return price == other.price && volume == other.volume && type == other.type;
    }
};

class OrderBook {
private:
    std::vector<Order> orders;

public:
    bool add_order(const Order& order) {
        int min = INT_MAX;
        int max = INT_MIN;
        if (order.type == OrderType::Buy)
        {
            for (int i = 0; i < orders.size(); i++)
            {
                if (orders[i].type == OrderType::Sell && orders[i].price < min)
                {
                    min = orders[i].price;
                }
            }
        }
        else
        {
            for (int i = 0; i < orders.size(); i++)
            {
                if (orders[i].type == OrderType::Buy && orders[i].price > max)
                {
                    max = orders[i].price;
                }
            }
        }
        if (order.type == OrderType::Buy)
        {
            if (order.price < min)
            {
                orders.push_back(order);
                return true;
            }
            else
            {
                std::cout << "Вы покупаете товар дороже чем минимальнцая цена в продаже" << std::endl;
                return false;
            }
        }
        else
        {
            if (order.price > max)
            {
                orders.push_back(order);
                return true;
            }
            else
            {
                std::cout << "Вы продаете товар дешевле чем максимальная цена в покупке" << std::endl;
                return false;

            }
        }
    }

    void change_order(const Order& old_order, const Order& new_order) {
        // Find the maximum buy and minimum sell orders
        auto max_buy = orders.end();
        auto min_sell = orders.end();

        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->type == OrderType::Buy) {
                if (max_buy == orders.end() || it->price > max_buy->price) {
                    max_buy = it;
                }
            }
            else if (it->type == OrderType::Sell) {
                if (min_sell == orders.end() || it->price < min_sell->price) {
                    min_sell = it;
                }
            }
        }

        // Check conditions for changing the order
        if (old_order.type == OrderType::Sell && new_order.type == OrderType::Sell) {
            if (new_order.price < max_buy->price) {
                std::cout << "Ошибка: Новая цена покупки ниже минимальной цены продажи\n";
                return;
            }
        }
        else if (old_order.type == OrderType::Buy && new_order.type == OrderType::Buy) {
            if (new_order.price > min_sell->price) {
                std::cout << "Ошибка: Новая цена продажи превышает максимальную цену покупки\n";
                return;
            }
        }


        auto old_it = std::find(orders.begin(), orders.end(), old_order);
        if (old_it != orders.end()) {
            orders.erase(old_it);
        }
        else {
            std::cout << "Ошибка: Не удалось найти заявку для изменения\n";
            return;
        }

        orders.push_back(new_order);
        std::cout << "Заявка успешно изменена\n";

    }

    void remove_order(const Order& order) {
        // Удалить заявку
        auto it = std::remove(orders.begin(), orders.end(), order);
        if (it != orders.end())
        {
            orders.erase(it, orders.end());
            std::cout << "Элемент/ты успешно удалены" << std::endl;
        }
        else
        {
            std::cout << "Элементы не были найдены, проверьте правильность ввода" << std::endl;
        }
    }

    void display_top_10_orders() {
        // Отсортировать заявки по цене и типу и отобразить лучшие 10
        int countBuy,countSell = 0;
        std::sort(orders.begin(), orders.end(), [&countBuy,&countSell](const Order& a, const Order& b) {
            if (a.type == OrderType::Buy && b.type == OrderType::Sell) {
                return false;
            }
            if (a.type == OrderType::Sell && b.type == OrderType::Buy) {
                return true;
            }
            if (a.type == OrderType::Buy && b.type == OrderType::Buy) {
                countBuy++;
                return a.price > b.price; // High to low
            }
            if (a.type == OrderType::Sell && b.type == OrderType::Sell) {
                countSell++;
                return a.price < b.price; // Low to high
            }
            return false;
            });

        int mid = -1,count = 0;
        for (const auto& it : orders)
        {
            if (it.type == OrderType::Buy) break;
            mid++;
        }
        std::vector<Order> vec_sells;
        for (int i = 0; i < std::min(5, mid); i++)
        {
            vec_sells.push_back(orders[i]);
        }
        reverse(vec_sells.begin(), vec_sells.end());
        if (mid < 5 || orders.size()<=10)
        {
            for (const Order& order : orders) {
                if (count >= 10) {
                    break;
                }
                std::string type_str = (order.type == OrderType::Buy) ? "Покупка" : "Продажа";
                std::cout << "Цена: " << order.price << ", Объем: " << order.volume << ", Тип: " << type_str << std::endl;
                count++;
            }
            return;
        }
        else
        {
            for (int i = 0; i < std::min(5, mid); i++)
            {
                std::string type_str = (vec_sells[i].type == OrderType::Buy) ? "Покупка" : "Продажа";
                std::cout << "Цена: " << vec_sells[i].price << ", Объем: " << vec_sells[i].volume << ", Тип: " << type_str << std::endl;
            }
            for (int i = mid+1; i < mid + 6; i++)
            {
                std::string type_str = (orders[i].type == OrderType::Buy) ? "Покупка" : "Продажа";
                std::cout << "Цена: " << orders[i].price << ", Объем: " << orders[i].volume << ", Тип: " << type_str << std::endl;
            }
        }
    }
};

class OrderBookTester {
private:
    OrderBook order_book;
    std::chrono::steady_clock::time_point start_display;
    std::chrono::steady_clock::time_point end_display;
public:
    OrderBookTester() {

        // Добавить заявки
        order_book.add_order({ 100.0, 10, OrderType::Buy });
        order_book.add_order({ 200.0, 20, OrderType::Sell  });
        order_book.add_order({ 150.0, 15, OrderType::Buy });
        order_book.add_order({ 101.0, 5, OrderType::Buy });
        order_book.add_order({ 102.0, 5, OrderType::Buy });
        order_book.add_order({ 103.0, 5, OrderType::Buy });
        order_book.add_order({ 104.0, 5, OrderType::Buy });
        order_book.add_order({ 105.0, 5, OrderType::Buy });
        order_book.add_order({ 200.0, 3, OrderType::Sell });
        order_book.add_order({ 201.0, 20, OrderType::Sell });
        order_book.add_order({ 202.0, 20, OrderType::Sell });
        order_book.add_order({ 203.0, 20, OrderType::Sell });
        order_book.add_order({ 204.0, 20, OrderType::Sell });
        order_book.add_order({ 205.0, 20, OrderType::Sell });
        

        // Отобразить первые 10 заявок
        std::cout << "Лучшие 10 заявок:\n";
        order_book.display_top_10_orders();

        // Изменить заявку
        Order new_order1(200, 1565, OrderType::Sell);
        order_book.change_order({ 200.0, 3, OrderType::Sell }, new_order1);

        std::cout << "\nУдаляем элемент с ценой 201, объемом 20, Тип <Продажа>\n";
        // Удалить заявку
        order_book.remove_order({ 201.0, 20, OrderType::Sell });

        // Отобразить обновленные первые 10 заявок
        std::cout << "\nОбновленные лучшие 10 заявок:\n";
        start_display = std::chrono::steady_clock::now();
        order_book.display_top_10_orders();
        end_display = std::chrono::steady_clock::now();
    }
    void AddOrder(double p,int v, int t)
    {
        if (t > 1 || t < 0) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
        order_book.add_order({ p,v,(OrderType)t });
    }
    void ChangeOrder(double p_old, int v_old, int t_old, double p_new, int v_new, int t_new)
    {
        if ((t_old > 1 || t_old < 0) && (t_new > 1 || t_new < 0)) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
        order_book.change_order({ p_old,v_old,(OrderType)t_old }, { p_new,v_new,(OrderType)t_new });
    }
    void RemoveOrder(double p, int v, int t)
    {
        if (t > 1 || t < 0) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
        order_book.remove_order({ p,v,(OrderType)t });
    }
    void Display_top10()
    {
        order_book.display_top_10_orders();
    }

    void measure_performance() {
        Order order(100.0, 10, OrderType::Buy);

        // Измерить время выполнения добавления заявки
        auto start = std::chrono::steady_clock::now();
        order_book.add_order(order);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\nВремя добавления заявки: " << duration << " микросекунд\n";
        
        // Измерить время выполнения изменения заявки
        start = std::chrono::steady_clock::now();
        order_book.change_order({ 100.0, 10, OrderType::Buy }, {100.0, 43, OrderType::Buy});
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\nВремя изменения заявки: " << duration << " микросекунд\n";

        // Измерить время выполнения удаления заявки
        start = std::chrono::steady_clock::now();
        order_book.remove_order(order);
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\nВремя удаления заявки: " << duration << " микросекунд\n";

        // Измерить время выполнения отображения 10 лучших заявок
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_display - start_display).count();
        std::cout << "\nВремя показа 10 лучших заявок: " << duration << " микросекунд\n";

    }
};

int main() {
    setlocale(LC_ALL, "ru");
    // Создание объекта класса OrderBookTester
    int symbol;
    OrderBookTester tester;
    // Тестирование функций класса OrderBook


    // Измерение производительности функций класса OrderBook
    tester.measure_performance();
    while (1)
    {
        std::cout << "\nВыберите действие:\n 1) Добавить заявку\n 2) Изменить заявку\n 3) Удалить заявку\n 4) Отобразить лучшие 10 заявок\n 5) Проверить скорость \n 6) Выйти из программы\n";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
            std::cin.clear(); // Сброс флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка вводного буфера
            continue;
        }
        switch (choice) {
        case 1:
            double price;
            int value;
            int type;
            std::cout << "\nВведите цену\n";
            std::cin >> price;
            std::cout << "\nВведите объем\n";
            std::cin >> value;
            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа\n";
            std::cin >> type;
            tester.AddOrder(price, value, type);
            break;
        case 2:
            double price_old,price_new;
            int value_old,value_new;
            int type_old,type_new;
            std::cout << "\nВведите цену элемента который нужно изменить\n";
            std::cin >> price_old;
            std::cout << "\nВведите объем элемента который нужно изменить\n";
            std::cin >> value_old;
            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа элемента который нужно изменить\n";
            std::cin >> type_old;
            std::cout << "\nВведите новое значение цены\n";
            std::cin >> price_new;
            std::cout << "\nВведите новое значение объема\n";
            std::cin >> value_new;
            std::cout << "\nВведите новый тип покупка или продажа, где 0 - покупка, 1 - продажа \n";
            std::cin >> type_new;
            tester.ChangeOrder(price_old, value_old, type_old, price_new, value_new, type_new);
            break;
        case 3:
            price;
            value;
            type;
            std::cout << "\nВведите цену\n";
            std::cin >> price;
            std::cout << "\nВведите объем\n";
            std::cin >> value;
            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа\n";
            std::cin >> type;
            tester.RemoveOrder(price, value, type);
            break;
        case 4:
            tester.Display_top10();
            break;
        case 5:
            tester.measure_performance();
            break;
        case 6:
            return 0;
        default:
            std::cout << "Некорректный выбор. Попробуйте еще раз.\n";
        }

    }

    return 0;
}