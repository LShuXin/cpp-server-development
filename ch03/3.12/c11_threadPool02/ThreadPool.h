//
// Created by apple on 2023/12/9.
//

#ifndef C11_THREADPOOL02_THREADPOOL_H
#define C11_THREADPOOL02_THREADPOOL_H

#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <mutex>
#include <memory>
#include <condition_variable>

class Task
{
public:
    Task(int taskID)
    {
        this->m_taskID = taskID;
    }

    virtual ~Task()
    {
        std::cout << "Task destructed, taskID: " << m_taskID << std::endl;
    }

    virtual void doTask()
    {
        std::cout << "Handling a task, taskID: " << m_taskID << std::endl;
    }

    unsigned int getId()
    {
        return m_taskID;
    }

private:
    unsigned int     m_taskID;
};


class ThreadPool final {
public:
    ThreadPool();
    ~ThreadPool();
    ThreadPool(const ThreadPool &rhs) = delete;
    ThreadPool& operator=(const ThreadPool &rhs) = delete;

public:
    void Init(int numTasks = 5);
    void Stop();
    void AddTask(Task* pTask);
    void RemoveAllTasks();

private:
    void threadFunc();

private:
    bool                                         m_bRunning;
    std::list<std::shared_ptr<Task>>             m_listTasks;
    std::vector<std::shared_ptr<std::thread>>    m_threads;
    std::mutex                                   m_mutexTasks;
    std::condition_variable                      m_cv;
};


#endif //C11_THREADPOOL02_THREADPOOL_H
