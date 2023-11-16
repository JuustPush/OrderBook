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
//                std::cout << "������: �� ��������� ����� ������, ��� ����������� ���� � �������" << std::endl;
//                return false;
//            }
//            else {
//                orders.emplace(order.price, order);
//                std::cout << "������ �� ������� ��������" << std::endl;
//                return true;
//            }
//        }
//        else if (order.type == OrderType::Sell) {
//            auto it = std::find_if(orders.begin(), orders.end(), [&](const auto& pair) {
//                return pair.second.type == OrderType::Buy && pair.second.price >= order.price;
//                });
//
//            if (it != orders.end()) {
//                std::cout << "������: �� �������� ����� �������, ��� ������������ ���� � �������" << std::endl;
//                return false;
//            }
//            else {
//                orders.emplace(order.price, order);
//                std::cout << "������ �� ������� ��������" << std::endl;
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
//                std::cout << "������ ������� ��������" << std::endl;
//                orders.erase(it);
//            }
//        }
//        else {
//            std::cout << "������: �� ������� ����� ������ ��� ���������" << std::endl;
//        }
//    }
//
//    void remove_order(const Order& order) {
//        auto it = orders.find(order.price);
//
//        if (it != orders.end() && it->second == order) {
//            orders.erase(it);
//            std::cout << "������ ������� �������" << std::endl;
//        }
//        else {
//            std::cout << "������: ������ �� �������" << std::endl;
//        }
//    }
//
//    void display_top_10_orders() {
//        // ������������� ������ �� ���� � ����
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
//                std::cout << "����: " << order.price << ", �����: " << order.volume << ", ���: �������\n";
//            }
//
//        if (!buy_orders.empty())
//            for (int i = 0; i < std::min(5, static_cast<int>(buy_orders.size())); ++i) {
//                const Order& order = buy_orders[i];
//                std::cout << "����: " << order.price << ", �����: " << order.volume << ", ���: �������\n";
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
//        // �������� ������
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
//        // ���������� ������ 10 ������
//        std::cout << "������ 10 ������:\n";
//        order_book.display_top_10_orders();
//
//        // �������� ������
//        Order new_order1(200, 1565, OrderType::Sell);
//        order_book.change_order({ 200.0, 3, OrderType::Sell }, new_order1);
//
//        std::cout << "\n������� ������� � ����� 201, ������� 20, ��� <�������>\n";
//        // ������� ������
//        order_book.remove_order({ 201.0, 20, OrderType::Sell });
//
//        // ���������� ����������� ������ 10 ������
//        std::cout << "\n����������� ������ 10 ������:\n";
//        start_display = std::chrono::steady_clock::now();
//        order_book.display_top_10_orders();
//        end_display = std::chrono::steady_clock::now();
//    }
//
//    void AddOrder(double p, int v, int t) {
//        if (t > 1 || t < 0) std::cout << "\n������������ ���� �������� �������/�������\n";
//        order_book.add_order({ p,v,(OrderType)t });
//    }
//
//    void ChangeOrder(double p_old, int v_old, int t_old, double p_new, int v_new, int t_new) {
//        if ((t_old > 1 || t_old < 0) && (t_new > 1 || t_new < 0)) std::cout << "\n������������ ���� �������� �������/�������\n";
//        order_book.change_order({ p_old,v_old,(OrderType)t_old }, { p_new,v_new,(OrderType)t_new });
//    }
//
//    void RemoveOrder(double p, int v, int t) {
//        if (t > 1 || t < 0) std::cout << "\n������������ ���� �������� �������/�������\n";
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
//        // �������� ����� ���������� ���������� ������
//        auto start = std::chrono::steady_clock::now();
//        order_book.add_order(order);
//        auto end = std::chrono::steady_clock::now();
//        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\n����� ���������� ������: " << duration << " �����������\n";
//
//        // �������� ����� ���������� ��������� ������
//        start = std::chrono::steady_clock::now();
//        order_book.change_order({ 100.0, 10, OrderType::Buy }, { 100.0, 43, OrderType::Buy });
//        end = std::chrono::steady_clock::now();
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\n����� ��������� ������: " << duration << " �����������\n";
//
//        // �������� ����� ���������� �������� ������
//        start = std::chrono::steady_clock::now();
//        order_book.remove_order({ 100.0, 43, OrderType::Buy });
//        end = std::chrono::steady_clock::now();
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//        std::cout << "\n����� �������� ������: " << duration << " �����������\n";
//
//        // �������� ����� ���������� ����������� 10 ������ ������
//        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_display - start_display).count();
//        std::cout << "\n����� ������ 10 ������ ������: " << duration << " �����������\n";
//    }
//};
//
//int main() {
//    setlocale(LC_ALL, "ru");
//    // �������� ������� ������ OrderBookTester
//    int symbol;
//    OrderBookTester tester;
//    // ������������ ������� ������ OrderBook
//
//    // ��������� ������������������ ������� ������ OrderBook
//    tester.measure_performance();
//    while (1) {
//        std::cout << "\n�������� ��������:\n 1) �������� ������\n 2) �������� ������\n 3) ������� ������\n 4) ���������� ������ 10 ������\n 5) ��������� �������� \n 6) ����� �� ���������\n";
//        int choice;
//        std::cin >> choice;
//
//        if (std::cin.fail()) {
//            std::cout << "������ �����. ����������, ������� �����.\n";
//            std::cin.clear(); // ����� ����� ������
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� �������� ������
//            continue;
//        }
//        switch (choice) {
//        case 1:
//            double price;
//            int value;
//            int type;
//            std::cout << "\n������� ����\n";
//            std::cin >> price;
//            std::cout << "\n������� �����\n";
//            std::cin >> value;
//            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - �������\n";
//            std::cin >> type;
//            tester.AddOrder(price, value, type);
//            break;
//        case 2:
//            double price_old, price_new;
//            int value_old, value_new;
//            int type_old, type_new;
//            std::cout << "\n������� ���� ��������, ������� ����� ��������\n";
//            std::cin >> price_old;
//            std::cout << "\n������� ����� ��������, ������� ����� ��������\n";
//            std::cin >> value_old;
//            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - ������� ��������, ������� ����� ��������\n";
//            std::cin >> type_old;
//            std::cout << "\n������� ����� �������� ����\n";
//            std::cin >> price_new;
//            std::cout << "\n������� ����� �������� ������\n";
//            std::cin >> value_new;
//            std::cout << "\n������� ����� ��� ������� ��� �������, ��� 0 - �������, 1 - ������� \n";
//            std::cin >> type_new;
//            tester.ChangeOrder(price_old, value_old, type_old, price_new, value_new, type_new);
//            break;
//        case 3:
//            price;
//            value;
//            type;
//            std::cout << "\n������� ����\n";
//            std::cin >> price;
//            std::cout << "\n������� �����\n";
//            std::cin >> value;
//            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - �������\n";
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
//            std::cout << "������������ �����. ���������� ��� ���.\n";
//        }
//    }
//
//    return 0;
//}
