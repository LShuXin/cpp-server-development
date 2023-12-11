#include <iostream>
#include <thread>
#include <sstream>

void worker_thread_func()
{
    while(true)
    {
    }
}


int main()
{
    std::thread worker_thread(worker_thread_func);
    std::thread::id worker_thread_id = worker_thread.get_id();
    std::cout << "worker threadID:" << worker_thread_id << std::endl;

    std::thread::id main_thread_id = std::this_thread::get_id();

    std::cout << main_thread_id << std::endl;

    std::ostringstream oss;
    oss << main_thread_id;
    
    std::cout << oss.str() << std::endl;

    std::cout << std::stoull(oss.str()) << std::endl;


    while (true)
    {
        
    }
    return 0;
}
