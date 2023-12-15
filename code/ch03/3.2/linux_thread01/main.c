#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
// mac 需要引入 <zconf.h>
#include <zconf.h>

void* threadfunc(void* argc)
{
    while (1)
    {
        // 睡眠1s
        sleep(1);
        printf(("I am a New Thread! \n"));
    }

    return NULL;
}

int main() {
    pthread_t threadid;
    pthread_create(&threadid, NULL, threadfunc, NULL);

    // 权宜之计，让主线程不要退出
    while (1)
    {

    }

    return 0;
}
