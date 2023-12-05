#include <pthread.h>
#include <stdio.h>
#include <errno.h>

int main()
{
    pthread_mutex_t mymutex;
    pthread_mutex_init(&mymutex, NULL);
    int ret = pthread_mutex_lock(&mymutex);

    // 尝试销毁被锁定的mutex对象
    ret = pthread_mutex_destroy(&mymutex);
    if (ret != 0)
    {
        if (ret == EBUSY)
        {
            printf("EBUSY\n");
        }
        printf("Failed to destroy mutex.\n");
    }

    ret = pthread_mutex_unlock(&mymutex);

    // 尝试销毁已经解锁的 mutex 对象
    ret = pthread_mutex_destroy(&mymutex);
    if (ret == 0)
    {
        printf("Success fo destroy mutex.\n");
    }

    return 0;
}
