#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 线程局部存储key
pthread_key_t thread_log_key;

// 每个线程会调用该函数写日志
void write_to_thread_log(const char* message)
{
    if (message == NULL)
    {
        return;
    }

    // 获取本线程的日志文件指针
    // 文件对象指针是在创建本线程时，手动创建 FILE* 后调用 pthread_setspecific 实现的
    FILE* logfile = (FILE*)pthread_getspecific(thread_log_key);
    fprintf(logfile, "%s\n", message);
    fflush(logfile);
}

// 当线程被关闭时会调用该函数
void close_thread_log(void* logfile)
{
    char msg_to_print[128] = { 0 };
    sprintf(msg_to_print, "close logfile: thread%ld.log\n", (unsigned long)pthread_self());
    printf(msg_to_print);
    fclose((FILE*)logfile);
}


/**
 * 建日志文件，写日志
 * */
void* thread_function(void* args)
{
    char logfilename[128] = { 0 };
    sprintf(logfilename, "thread%ld.log", (unsigned long)pthread_self());
    FILE* logfile = fopen(logfilename, "w");
    if (logfile != NULL)
    {
        pthread_setspecific(thread_log_key, logfile);
        write_to_thread_log("thread start...");
    }

    return NULL;
}



int main() {
    pthread_t threads[5];
    pthread_key_create(&thread_log_key, close_thread_log);

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
