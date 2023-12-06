#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <list>
#include <semaphore.h>
#include <iostream>

class Task
{
public:
    Task(int taskID)
    {
        this->taskID = taskID;
    }
    void doTask()
    {
        std::cout << "handle a task, taskID: " << taskID << " threadID: " << pthread_self() << std::endl;
    }
private:
    int taskID;
};

pthread_mutex_t  mymutex;
std::list<Task*> tasks;
pthread_cond_t mycv;

void* consumer_thread(void* param)
{
    Task* pTask = NULL;
    while (true)
    {
        pthread_mutex_lock(&mymutex);

        while (tasks.empty())
        {
            // 如果获得了互斥锁 mymutex，但是条件不合适，这 pthread_cond_wait 会释放锁，不往下执行
            // 发生变化后，如果条件合适，则 pthread_cond_wait 将直接获得锁
            pthread_cond_wait(&mycv, &mymutex);
        }

        pTask = tasks.front();
        tasks.pop_front();

        pthread_mutex_unlock(&mymutex);

        if (pTask == NULL)
        {
            continue;;
        }

        pTask->doTask();
        delete pTask;
        pTask = NULL;
    }

    return NULL;
}

void* producer_thread(void* param)
{
    Task* pTask = NULL;
    int taskID = 0;

    while (true)
    {
        pthread_mutex_unlock(&mymutex);
        pTask = new Task(taskID);
        tasks.push_back(pTask);
        std::cout << "produce a task, taskID: " << taskID << ", threadID:" << pthread_self() << std::endl;
        pthread_mutex_unlock(&mymutex);

        pthread_cond_signal(&mycv);

        taskID++;
        sleep(2);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&mymutex, NULL);
    pthread_cond_init(&mycv, NULL);

    // 创建5个消费者线程
    pthread_t consumerThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&consumerThreadID[i], NULL, consumer_thread, NULL);
    }

    // 创建一个生产者线程
    pthread_t producerThreadID;
    pthread_create(&producerThreadID, NULL, producer_thread, NULL);

    pthread_join(producerThreadID, NULL);
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(consumerThreadID[i], NULL);
    }


    pthread_mutex_destroy(&mymutex);
    pthread_cond_destroy(&mycv);

    return 0;
}
