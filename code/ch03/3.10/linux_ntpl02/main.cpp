#include <iostream>
#include <pthread.h>
#include <unistd.h>

// 线程局部存储key
__thread int g_data = 1;

void* workerThreadFunction1(void* args)
{
    while (true)
    {
        ++g_data;
    }
    return NULL;
}

void* workerThreadFunction2(void* args)
{
    while (true)
    {
        std::cout << "g_data: " << g_data << " threadID: " << (unsigned long)pthread_self() << std::endl;
    }
    return NULL;
}


int main() {
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, workerThreadFunction1, NULL);
    pthread_create(&threads[1], NULL, workerThreadFunction2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}
