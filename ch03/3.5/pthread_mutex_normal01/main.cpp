#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

pthread_mutex_t   mymutex;
int               resoureNo = 6;

void* worker_thread(void* params)
{
    pthread_t threadID = pthread_self();
    printf("Thread start, ThreadID: %d\n", threadID);

    while (true)
    {
        pthread_mutex_lock(&mymutex);
        printf("Mutex lock, resourceNo: %d, ThreadID: %d\n", resoureNo, threadID);
        resoureNo++;

        printf("Mutex unlock, resourceNo: %d, ThreadID: %d\n", resoureNo, threadID);
        pthread_mutex_unlock(&mymutex);

        // 休眠1秒
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(&mymutex, &mutexattr);

    // 创建了5个工作线程
    pthread_t threadID[5];
    for (int i = 0; i < 5; ++i)
    {
        pthread_create(&threadID[i], NULL, worker_thread, NULL);
    }

    for (int i = 0; i < 5; ++i)
    {
        pthread_join(threadID[i], NULL);
    }

    pthread_mutex_destroy(&mymutex);
    pthread_mutexattr_destroy(&mutexattr);

    return 0;
}
