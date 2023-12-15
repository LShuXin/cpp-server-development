#include <iostream>
#include <unistd.h>
#include <pthread.h>

int resourceID = 0;
pthread_rwlock_t myrwlock;

void* read_thread(void* param)
{
    while (true)
    {
        // 请求读锁
        pthread_rwlock_rdlock(&myrwlock);

        // 使用睡眠模拟读线程读的过程花了很长时间
        std::cout << "read threadID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

void* write_thread(void* param)
{
    while (true)
    {
        // 申请写锁
        pthread_rwlock_wrlock(&myrwlock);

        resourceID++;
        std::cout << "write threadID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        pthread_rwlock_unlock(&myrwlock);

        // 让写线程有更多的空闲时间，从而让读线程有更多竞争锁的机会
        sleep(1);
    }
}


int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&myrwlock, &attr);

    // 创建5个请求读锁线程
    pthread_t readThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&readThreadID[i], NULL, read_thread, NULL);
    }

    // 创建1个请求写锁线程
    pthread_t writeThreadID;
    pthread_create(&writeThreadID, NULL, write_thread, NULL);

    pthread_join(writeThreadID, NULL);
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(readThreadID[i], NULL);
    }

    pthread_rwlock_destroy(&myrwlock);

    return 0;
}