#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <algorithm>

enum class OrderType {
    Buy,
    Sell
};

struct Order {
    double price;
    int volume;
    OrderType type;

    Order() : price(0.0), volume(0), type(OrderType::Buy) {}

    Order(double p, int v, OrderType t) : price(p), volume(v), type(t) {}

    bool operator<(const Order& other) const {
        return price < other.price;
    }

    bool operator>(const Order& other) const {
        return price > other.price;
    }

    bool operator==(const Order& other) const {
        return price == other.price && volume == other.volume && type == other.type;
    }
    bool operator!=(const Order& other) const {
        return !(*this == other);
    }

};

class OrderBook {
private:
    std::priority_queue<Order> buy_orders;   
    std::priority_queue<Order, std::vector<Order>, std::greater<>> sell_orders;  

public:
    bool add_order(const Order& order) {
        if (order.type == OrderType::Buy) {
            if (!sell_orders.empty() && order.price >= sell_orders.top().price) {
                std::cout << "������: �� ��������� ����� ������, ��� ����������� ���� � �������" << std::endl;
                return false;
            }
            else {
                buy_orders.push(order);
                return true;
            }
        }
        else if (order.type == OrderType::Sell) {
            if (!buy_orders.empty() && order.price <= buy_orders.top().price) {
                std::cout << "������: �� �������� ����� �������, ��� ������������ ���� � �������" << std::endl;
                return false;
            }
            else {
                sell_orders.push(order);
                return true;
            }
        }
    }



    bool find_order_buy(const Order& order, std::priority_queue<Order> orders) {
        std::priority_queue<Order> temp;
        bool found = false;
        while (!orders.empty()) {
            if (orders.top() == order) {
                found = true;
                break;
            }
            temp.push(orders.top());
            orders.pop();
        }
        while (!temp.empty()) {
            orders.push(temp.top());
            temp.pop();
        }
        return found;
    }
    bool find_order_sell(const Order& order, std::priority_queue<Order, std::vector<Order>, std::greater<>> orders) {
        std::priority_queue<Order> temp;
        bool found = false;
        while (!orders.empty()) {
            if (orders.top() == order) {
                found = true;
                break;
            }
            temp.push(orders.top());
            orders.pop();
        }
        while (!temp.empty()) {
            orders.push(temp.top());
            temp.pop();
        }
        return found;
    }

    void change_order(const Order& old_order, const Order& new_order) {
        if (old_order.type == OrderType::Buy) {
            std::priority_queue<Order> temp;
            bool found = false;
            while (!buy_orders.empty()) {
                if (buy_orders.top() == old_order) {
                    found = true;
                    break;
                }
                temp.push(buy_orders.top());
                buy_orders.pop();
            }
            while (!temp.empty()) {
                if (temp.top() != old_order) {
                    buy_orders.push(temp.top());
                }
                temp.pop();
            }
            if (found) {
                if (remove_order(old_order)) 
                {
                    if (add_order(new_order))    
                        std::cout << "������ ������� ��������" << std::endl;
                    else
                    {
                        add_order(old_order);
                    }
                }
            }
            else {
                std::cout << "�� ������ ������� ��� ���������" << std::endl;
            }
        }
        else if (old_order.type == OrderType::Sell) {
            std::priority_queue<Order, std::vector<Order>, std::greater<>> temp;
            bool found = false;
            while (!sell_orders.empty()) {
                if (sell_orders.top() == old_order) {
                    found = true;
                    break;
                }
                temp.push(sell_orders.top());
                sell_orders.pop();
            }
            while (!temp.empty()) {
                if (temp.top() != old_order) {
                    sell_orders.push(temp.top());
                }
                temp.pop();
            }
            if (found) {
                if (remove_order(old_order)) 
                {
                    if (add_order(new_order))   
                        std::cout << "������ ������� ��������" << std::endl;
                    else
                    {
                        add_order(old_order);
                    }
                }
            }
            else {
                std::cout << "�� ������ ������� ��� ���������" << std::endl;
            }
        }
    }



    bool remove_order(const Order& order) {
        if (order.type == OrderType::Buy) {
            std::priority_queue<Order> temp;
            bool found = false;
            while (!buy_orders.empty()) {
                if (buy_orders.top() == order) {
                    found = true;
                    buy_orders.pop();
                    break;
                }
                temp.push(buy_orders.top());
                buy_orders.pop();
            }
            while (!temp.empty()) {
                buy_orders.push(temp.top());
                temp.pop();
            }
            if (!found) {
                std::cout << "������ �� �������" << std::endl;
                return false;
            }
        }
        else if (order.type == OrderType::Sell) {
            std::priority_queue<Order, std::vector<Order>, std::greater<>> temp;
            bool found = false;
            while (!sell_orders.empty()) {
                if (sell_orders.top() == order) {
                    found = true;
                    sell_orders.pop();
                    break;
                }
                temp.push(sell_orders.top());
                sell_orders.pop();
            }
            while (!temp.empty()) {
                sell_orders.push(temp.top());
                temp.pop();
            }
            if (!found) {
                std::cout << "������ �� �������" << std::endl;
                return false;
            }
        }

        std::cout << "������ ������� �������" << std::endl;
        return true;
    }


    void display_top_10_orders() {
        std::priority_queue<Order> temp_buy_orders = buy_orders;
        std::priority_queue<Order, std::vector<Order>, std::greater<>> temp_sell_orders = sell_orders;
        std::vector<Order> temp_sell_vector;

        int sell_count = 0;
        while (sell_count < 5 && !temp_sell_orders.empty()) {
            const Order& order = temp_sell_orders.top();
            temp_sell_vector.push_back(order);

            temp_sell_orders.pop();
            sell_count++;
        }
        reverse(temp_sell_vector.begin(), temp_sell_vector.end());
        for (const auto& it : temp_sell_vector)
        {
            std::cout << "����: " << it.price << ", �����: " << it.volume << ", ���: �������\n";
        }

        int buy_count = 0;
        while (buy_count < 5 && !temp_buy_orders.empty()) {
            const Order& order = temp_buy_orders.top();
            std::cout << "����: " << order.price << ", �����: " << order.volume << ", ���: �������\n";
            temp_buy_orders.pop();
            buy_count++;
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
        // Add sample orders
        order_book.add_order({ 100.0, 10, OrderType::Buy });
        order_book.add_order({ 200.0, 20, OrderType::Sell });
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


        std::cout << "������ 10 ������:\n";
        order_book.display_top_10_orders();

        Order new_order1(200, 1565, OrderType::Sell);
        order_book.change_order({ 200.0, 3, OrderType::Sell }, new_order1);

        std::cout << "\n������� ������� � ����� 201, ������� 20, ��� <�������>\n";

        order_book.remove_order({ 201.0, 20, OrderType::Sell });

        std::cout << "\n����������� ������ 10 ������:\n";
        start_display = std::chrono::steady_clock::now();
        order_book.display_top_10_orders();
        end_display = std::chrono::steady_clock::now();
    }

    void AddOrder(double p, int v, int t) {
        if (t > 1 || t < 0) std::cout << "\n������������ ���� �������� �������/�������\n";
        order_book.add_order({ p, v, static_cast<OrderType>(t) });
    }

    void ChangeOrder(double p_old, int v_old, int t_old, double p_new, int v_new, int t_new) {
        if ((t_old > 1 || t_old < 0) && (t_new > 1 || t_new < 0))
            std::cout << "\n������������ ���� �������� �������/�������\n";
        order_book.change_order({ p_old, v_old, static_cast<OrderType>(t_old) },
            { p_new, v_new, static_cast<OrderType>(t_new) });
    }

    void RemoveOrder(double p, int v, int t) {
        if (t > 1 || t < 0) std::cout << "\n������������ ���� �������� �������/�������\n";
        order_book.remove_order({ p, v, static_cast<OrderType>(t) });
    }

    void Display_top10() {
        order_book.display_top_10_orders();
    }

    void measure_performance() {
        Order order(100.0, 10, OrderType::Buy);

        // Measure the time taken to add an order
        auto start = std::chrono::steady_clock::now();
        order_book.add_order(order);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\n����� ���������� ������: " << duration << " �����������\n";

        // Measure the time taken to change an order
        start = std::chrono::steady_clock::now();
        order_book.change_order({ 100.0, 10, OrderType::Buy }, { 100.0, 43, OrderType::Buy });
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\n����� ��������� �����: " << duration << " �����������\n";

        // Measure the time taken to remove an order
        start = std::chrono::steady_clock::now();
        order_book.remove_order({ 100.0, 43, OrderType::Buy });
        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "\n����� �������� ������: " << duration << " �����������\n";

        // Measure the time taken to display the top 10 orders
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end_display - start_display).count();
        std::cout << "\n����� ������ 10 ������ ������: " << duration << " �����������\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    int symbol;
    OrderBookTester tester;

    tester.measure_performance();

    while (1) {
        std::cout << "\n�������� ��������:\n 1) �������� ������\n 2) �������� ������\n 3) ������� ������\n 4) ���������� ������ 10 ������\n 5) ��������� �������� \n 6) ����� �� ���������\n";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "������ �����. ����������, ������� �����.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1:
            double price;
            int volume;
            int type;
            std::cout << "\n������� ����\n";
            std::cin >> price;
            std::cout << "\n������� �����:\n";
            std::cin >> volume;
            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - �������\n";
            std::cin >> type;
            tester.AddOrder(price, volume, type);
            break;
        case 2:
            double price_old,price_new;
            int value_old,value_new;
            int type_old,type_new;
            std::cout << "\n������� ���� �������� ������� ����� ��������\n";
            std::cin >> price_old;
            std::cout << "\n������� ����� �������� ������� ����� ��������\n";
            std::cin >> value_old;
            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - ������� �������� ������� ����� ��������\n";
            std::cin >> type_old;
            std::cout << "\n������� ����� �������� ����\n";
            std::cin >> price_new;
            std::cout << "\n������� ����� �������� ������\n";
            std::cin >> value_new;
            std::cout << "\n������� ����� ��� ������� ��� �������, ��� 0 - �������, 1 - ������� \n";
            std::cin >> type_new;
            tester.ChangeOrder(price_old, value_old, type_old, price_new, value_new, type_new);
            break;
        case 3:
            price;
            volume;
            type;
            std::cout << "\n������� ����\n";
            std::cin >> price;
            std::cout << "\n������� �����\n";
            std::cin >> volume;
            std::cout << "\n������� ��� ������� ��� �������, ��� 0 - �������, 1 - �������\n";
            std::cin >> type;
            tester.RemoveOrder(price, volume, type);
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
            std::cout << "������������ �����. ���������� ��� ���.\n";
        }
    }

    return 0;
}
