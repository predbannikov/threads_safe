#include <iostream>
#include <atomic>
#include <thread>
#include <random>

using namespace std;

int value = 0;
using Ticket = size_t;
std::atomic<Ticket> owner_ticket{0};
std::atomic<Ticket> next_free_ticket{0};



void f() {
    int time_wait = std::rand()%5;
    Ticket my_ticket = next_free_ticket.fetch_add(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(time_wait));
    size_t tmp = 0;
    while (owner_ticket.load() != my_ticket) {
        tmp++;
        std::this_thread::yield();  // Закомментировать строку для просмотра разницы количества входа в цикл
    }
    cout << "value = " << my_ticket << " time_wait = " << time_wait << " buse waiting = " << tmp << endl;
    owner_ticket.fetch_add(1);
}

int main()
{
    std::srand(1010);
    atomic<bool> lock;
    size_t count_thread = thread::hardware_concurrency();
    thread t[count_thread];
    cout << "hardware concurrency = " << count_thread << endl;

    for (int i = 0; i < count_thread; i++) {
        t[i] = thread(f);
    }

    for (int i = 0; i < count_thread; i++)
        t[i].join();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return 0;
}
