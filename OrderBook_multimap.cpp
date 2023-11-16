//#include <iostream>
//#include <map>
//#include <chrono>
//#include <vector>
//#include <algorithm>
//#include <limits>
//enum class OrderType {
//    Buy,
//    Sell
//};
//
//struct Order {
//    double price;
//    int volume;
//    OrderType type;
//
//    Order() : price(0.0), volume(0), type(OrderType::Buy) {}
//
//    Order(double p, int v, OrderType t) : price(p), volume(v), type(t) {}
//
//    bool operator<(const Order& other) const {
//        return price < other.price;
//    }
//
//    bool operator==(const Order& other) const {
//        return price == other.price && volume == other.volume && type == other.type;
//    }
//};
//class OrderBook {
//private:
//    std::multimap<double, Order> orders;
//
//public:
//    double maxBuyPrice = std::numeric_limits<double>::lowest();
//    double minSellPrice = std::numeric_limits<double>::max();
//
//
//    bool add_order(const Order& order) {
//        if (order.type == OrderType::Buy) {
//            auto it = std::find_if(orders.begin(), orders.end(), [&](const auto& pair) {
//                return pair.second.type == OrderType::Sell && pair.second.price <= order.price;
//                });
//
//            if (it != orders.end()) {
//                std::cout << "Ошибка: Вы покупаете товар дороже, чем минимальная цена в продаже" << std::endl;
//                return false;
//            }
//            else {
//                orders.emplace(order.price, order);
//                std::cout << "Заявка на покупку одобрена" << std::endl;
//                return true;
//            }
//        }
//        else if (order.type == OrderType::Sell) {
//            auto it = std::find_if(orders.begin(), orders.end(), [&](const auto& pair) {
//                return pair.second.type == OrderType::Buy && pair.second.price >= order.price;
//                });
//
//            if (it != orders.end()) {
//                std::cout << "Ошибка: Вы продаете товар дешевле, чем максимальная цена в покупке" << std::endl;
//                return false;
//            }
//            else {
//                orders.emplace(order.price, order);
//                std::cout << "Заявка на продажу одобрена" << std::endl;
//                return true;
//            }
//        }
//    }
//
//    void change_order(const Order& old_order, const Order& new_order) {
//        auto range = orders.equal_range(old_order.price);
//        auto it = std::find_if(range.first, range.second, [&](const auto& pair) {
//            return pair.second == old_order;
//            });
//
//        if (it != orders.end()) {
//            
//            if (add_order(new_order))
//            {
//                std::cout << "Заявка успешно изменена" << std::endl;
//                orders.erase(it);
//            }
//        }
//        else {
//            std::cout << "Ошибка: Не удалось найти заявку для изменения" << std::endl;
//        }
//    }
//
//    void remove_order(const Order& order) {
//        auto it = orders.find(order.price);
//
//        if (it != orders.end() && it->second == order) {
//            orders.erase(it);
//            std::cout << "Заявка успешно удалена" << std::endl;
//        }
//        else {
//            std::cout << "Ошибка: заявка не найдена" << std::endl;
//        }
//    }
//
//    void display_top_10_orders() {
//        // Отсортировать заявки по цене и типу
//        std::vector<Order> sell_orders;
//        std::vector<Order> buy_orders;
//
//        for (const auto& entry : orders) {
//            if (entry.second.type == OrderType::Sell) {
//                sell_orders.push_back(entry.second);
//            }
//            else {
//                buy_orders.push_back(entry.second);
//            }
//        }
//
//        std::sort(sell_orders.begin(), sell_orders.end(), [](const Order& a, const Order& b) {
//            return a.price < b.price; // Low to high
//            });
//
//        std::sort(buy_orders.begin(), buy_orders.end(), [](const Order& a, const Order& b) {
//            return a.price > b.price; // High to low
//            });
//
//        if (!sell_orders.empty())
//            for (int i = std::min(4, static_cast<int>(sell_orders.size())); i >= 0; --i) {
//                const Order& order = sell_orders[i];
//                std::cout << "Цена: " << order.price << ", Объем: " << order.volume << ", Тип: Продажа\n";
//            }
//
//        if (!buy_orders.empty())
//            for (int i = 0; i < std::min(5, static_cast<int>(buy_orders.size())); ++i) {
//                const Order& order = buy_orders[i];
//                std::cout << "Цена: " << order.price << ", Объем: " << order.volume << ", Тип: Покупка\n";
//            }
//    }
//
//};
//
//class OrderBookTester {
//private:
//    OrderBook order_book;
//    std::chrono::steady_clock::time_point start_display;
//    std::chrono::steady_clock::time_point end_display;
//
//public:
//public:
//    OrderBookTester() {
//        // Добавить заявки
//        order_book.add_order({ 100.0, 10, OrderType::Buy });
//        order_book.add_order({ 200.0, 20, OrderType::Sell });
//        order_book.add_order({ 150.0, 15, OrderType::Buy });
//        order_book.add_order({ 101.0, 5, OrderType::Buy });
//        order_book.add_order({ 102.0, 5, OrderType::Buy });
//        order_book.add_order({ 103.0, 5, OrderType::Buy });
//        order_book.add_order({ 104.0, 5, OrderType::Buy });
//        order_book.add_order({ 105.0, 5, OrderType::Buy });
//        order_book.add_order({ 200.0, 3, OrderType::Sell });
//        order_book.add_order({ 201.0, 20, OrderType::Sell });
//        order_book.add_order({ 202.0, 20, OrderType::Sell });
//        order_book.add_order({ 203.0, 20, OrderType::Sell });
//        order_book.add_order({ 204.0, 20, OrderType::Sell });
//        order_book.add_order({ 205.0, 20, OrderType::Sell });
//
//        // Отобразить первые 10 заявок
//        std::cout << "Лучшие 10 заявок:\n";
//        order_book.display_top_10_orders();
//
//        // Изменить заявку
//        Order new_order1(200, 1565, OrderType::Sell);
//        order_book.change_order({ 200.0, 3, OrderType::Sell }, new_order1);
//
//        std::cout << "\nУдаляем элемент с ценой 201, объемом 20, Тип <Продажа>\n";
//        // Удалить заявку
//        order_book.remove_order({ 201.0, 20, OrderType::Sell });
//
//        // Отобразить обновленные первые 10 заявок
//        std::cout << "\nОбновленные лучшие 10 заявок:\n";
//        start_display = std::chrono::steady_clock::now();
//        order_book.display_top_10_orders();
//        end_display = std::chrono::steady_clock::now();
//    }
//
//    void AddOrder(double p, int v, int t) {
//        if (t > 1 || t < 0) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
//        order_book.add_order({ p,v,(OrderType)t });
//    }
//
//    void ChangeOrder(double p_old, int v_old, int t_old, double p_new, int v_new, int t_new) {
//        if ((t_old > 1 || t_old < 0) && (t_new > 1 || t_new < 0)) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
//        order_book.change_order({ p_old,v_old,(OrderType)t_old }, { p_new,v_new,(OrderType)t_new });
//    }
//
//    void RemoveOrder(double p, int v, int t) {
//        if (t > 1 || t < 0) std::cout << "\nнеправильный ввод операции покупка/продажа\n";
//        order_book.remove_order({ p,v,(OrderType)t });
//    }
//
//    void Display_top10() {
//        order_book.display_top_10_orders();
//    }
//
//    void measure_performance() {
//        Order order(100.0, 10, OrderType::Buy);
//
//        // Измерить время выполнения добавления заявки
//        auto start = std::chrono::steady_clock::now();
//        order_book.add_order(order);
//        auto end = std::chrono::steady_clock::now();
//        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\nВремя добавления заявки: " << duration << " микросекунд\n";
//
//        // Измерить время выполнения изменения заявки
//        start = std::chrono::steady_clock::now();
//        order_book.change_order({ 100.0, 10, OrderType::Buy }, { 100.0, 43, OrderType::Buy });
//        end = std::chrono::steady_clock::now();
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\nВремя изменения заявки: " << duration << " микросекунд\n";
//
//        // Измерить время выполнения удаления заявки
//        start = std::chrono::steady_clock::now();
//        order_book.remove_order({ 100.0, 43, OrderType::Buy });
//        end = std::chrono::steady_clock::now();
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\nВремя удаления заявки: " << duration << " микросекунд\n";
//
//        // Измерить время выполнения отображения 10 лучших заявок
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_display - start_display).count();
//        std::cout << "\nВремя показа 10 лучших заявок: " << duration << " микросекунд\n";
//    }
//};
//
//int main() {
//    setlocale(LC_ALL, "ru");
//    // Создание объекта класса OrderBookTester
//    int symbol;
//    OrderBookTester tester;
//    // Тестирование функций класса OrderBook
//
//    // Измерение производительности функций класса OrderBook
//    tester.measure_performance();
//    while (1) {
//        std::cout << "\nВыберите действие:\n 1) Добавить заявку\n 2) Изменить заявку\n 3) Удалить заявку\n 4) Отобразить лучшие 10 заявок\n 5) Проверить скорость \n 6) Выйти из программы\n";
//        int choice;
//        std::cin >> choice;
//
//        if (std::cin.fail()) {
//            std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";
//            std::cin.clear(); // Сброс флага ошибки
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка вводного буфера
//            continue;
//        }
//        switch (choice) {
//        case 1:
//            double price;
//            int value;
//            int type;
//            std::cout << "\nВведите цену\n";
//            std::cin >> price;
//            std::cout << "\nВведите объем\n";
//            std::cin >> value;
//            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа\n";
//            std::cin >> type;
//            tester.AddOrder(price, value, type);
//            break;
//        case 2:
//            double price_old, price_new;
//            int value_old, value_new;
//            int type_old, type_new;
//            std::cout << "\nВведите цену элемента, который нужно изменить\n";
//            std::cin >> price_old;
//            std::cout << "\nВведите объем элемента, который нужно изменить\n";
//            std::cin >> value_old;
//            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа элемента, который нужно изменить\n";
//            std::cin >> type_old;
//            std::cout << "\nВведите новое значение цены\n";
//            std::cin >> price_new;
//            std::cout << "\nВведите новое значение объема\n";
//            std::cin >> value_new;
//            std::cout << "\nВведите новый тип покупка или продажа, где 0 - покупка, 1 - продажа \n";
//            std::cin >> type_new;
//            tester.ChangeOrder(price_old, value_old, type_old, price_new, value_new, type_new);
//            break;
//        case 3:
//            price;
//            value;
//            type;
//            std::cout << "\nВведите цену\n";
//            std::cin >> price;
//            std::cout << "\nВведите объем\n";
//            std::cin >> value;
//            std::cout << "\nВведите тип покупка или продажа, где 0 - покупка, 1 - продажа\n";
//            std::cin >> type;
//            tester.RemoveOrder(price, value, type);
//            break;
//        case 4:
//            tester.Display_top10();
//            break;
//        case 5:
//            tester.measure_performance();
//            break;
//        case 6:
//            return 0;
//        default:
//            std::cout << "Некорректный выбор. Попробуйте еще раз.\n";
//        }
//    }
//
//    return 0;
//}
