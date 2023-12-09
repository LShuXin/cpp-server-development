//
// Created by apple on 2023/12/9.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool() {
    m_bRunning = false;
}

ThreadPool::~ThreadPool() {
    RemoveAllTasks();
}

void ThreadPool::Init(int numTasks) {
    m_bRunning = true;

    if (numTasks <= 0)
    {
        numTasks = 5;
    }

    std::shared_ptr<std::thread> spThread;
    for (int i = 0; i < numTasks; ++i)
    {
        spThread.reset(new std::thread(std::bind(&ThreadPool::threadFunc, this)));
        m_threads.push_back(spThread);
    }
}

void ThreadPool::threadFunc() {
    std::shared_ptr<Task> spTask = NULL;
    while (true)
    {
        {
            std::unique_lock<std::mutex> guard(m_mutexTasks);
            while (m_listTasks.empty())
            {
                if (!m_bRunning)
                {
                    break;
                }
                m_cv.wait(guard);
            }

            if (!m_bRunning)
            {
                break;
            }

            spTask = m_listTasks.front();
            m_listTasks.pop_front();
        }

        if (spTask == NULL)
        {
            break;
        }
        spTask->doTask();
        spTask.reset();
    }

    std::cout << "WorkerThread[" << std::this_thread::get_id() << "] exited";
}

void ThreadPool::Stop()
{
    m_bRunning = false;

    m_cv.notify_all();

    for (auto& iter: m_threads)
    {
        if (iter->joinable())
        {
            iter->join();
        }
    }
}

void ThreadPool::RemoveAllTasks()
{
    std::unique_lock<std::mutex>  guard(m_mutexTasks);

    for (auto& iter: m_listTasks)
    {
        iter.reset();
    }

    m_listTasks.clear();
}

void ThreadPool::AddTask(Task *pTask)
{
    std::shared_ptr<Task> spTask = NULL;
    spTask.reset(pTask);

    {
        std::unique_lock<std::mutex> guard(m_mutexTasks);
        m_listTasks.push_back(spTask);
    }
    m_cv.notify_one();

    std::cout << "New Task added, taskID:" << pTask->getId() << std::endl;
}
