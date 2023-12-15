#include <iostream>
#include <chrono>
#include "ThreadPool.h"

//class Task1 : public Task {
//public:
//    Task1(int taskID): Task(taskID)
//    {
//
//    }
//    void doTask() override {
//        while (true) {
//            std::cout << "loop handle1, taskID:" << getId() << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(2));
//        }
//    }
//};
//
//class Task2 : public Task {
//public:
//    Task2(int taskID): Task(taskID) {
//
//    }
//    void doTask() override {
//        while (true) {
//            std::cout << "loop handle2, taskID:" << getId() << std::endl;
//            std::this_thread::sleep_for(std::chrono::seconds(2));
//        }
//    }
//};

int main() {
    ThreadPool threadPool;
    threadPool.Init(5);

    for (int i = 0; i < 100; ++i)
    {
        threadPool.AddTask(new Task(i));
    }

//    threadPool.AddTask(new Task1(101));
//    threadPool.AddTask((new Task2(102)));

    std::this_thread::sleep_for(std::chrono::seconds(10));
    threadPool.Stop();

    return 0;
}
