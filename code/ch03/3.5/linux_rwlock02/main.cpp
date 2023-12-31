#include <pthread.h>
#include <unistd.h>
#include <iostream>

int resourceID = 0;
pthread_rwlock_t myrwlock;

void* read_thread(void* param)
{
    while (true)
    {
        //请求读锁
        pthread_rwlock_rdlock(&myrwlock);

        std::cout << "read thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

void* write_thread(void* param)
{
    while (true)
    {
        //请求写锁
        pthread_rwlock_wrlock(&myrwlock);

        ++resourceID;
        std::cout << "write thread ID: " << pthread_self() << ", resourceID: " << resourceID << std::endl;

        //使用睡眠模拟读线程读的过程消耗了很久的时间
        sleep(1);

        pthread_rwlock_unlock(&myrwlock);
    }

    return NULL;
}

int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    // 设置成请求写锁优先
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&myrwlock, &attr);

    // 创建5个请求读锁线程
    pthread_t readThreadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&readThreadID[i], NULL, read_thread, NULL);
    }

    // 创建一个请求写锁线程
    pthread_t writeThreadID;
    pthread_create(&writeThreadID, NULL, write_thread, NULL);

    pthread_join(writeThreadID, NULL);
    for (int i = 0; i < 5; ++i)
    {
        pthread_join(readThreadID[i], NULL);
    }

    return 0;
}