#include <iostream>
// 这里是thread而不是pthread.h
#include <thread>
#include <chrono>

thread_local int g_data = 1;

void worker_func1()
{
    while (true)
    {
        ++g_data;
    }
}

void worker_func2()
{
    while (true)
    {
        std::cout << "g_data: " << g_data << " threadID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

int main() {
    std::thread t1(worker_func1);
    std::thread t2(worker_func2);

    t1.join();
    t2.join();

    return 0;
}
