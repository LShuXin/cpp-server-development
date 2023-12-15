#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main() {
    pthread_mutex_t mymutex;
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(&mymutex, &mutexattr);

    int ret = pthread_mutex_lock(&mymutex);
    printf("ret = %d\n", ret);

    ret = pthread_mutex_lock(&mymutex);
    printf("ret = %d\n", ret);

    pthread_mutex_destroy(&mymutex);
    pthread_mutexattr_destroy(&mutexattr);

    return 0;
}
