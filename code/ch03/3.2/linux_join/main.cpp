#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define TIME_FILENAME "time.txt"

void* fileThreadFunc(void* arg)
{
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char timeStr[32] = {0};
    snprintf(timeStr, 32, "%04d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec
            );

    FILE* fp = fopen(TIME_FILENAME,"w");
    if (fp == NULL)
    {
        printf("Failed to create time.txt\n");
        return NULL;
    }

    // 这里多拷贝1个空字符字节
    size_t sizeToWrite = strlen(timeStr) + 1;
    size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
    if (ret != sizeToWrite)
    {
        printf("Write file error\n");
    }

    fclose(fp);
    return NULL;
}

int main()
{
    pthread_t fileThreadID;
    int ret = pthread_create(&fileThreadID, NULL, fileThreadFunc, NULL);
    if (ret != 0)
    {
        printf("Failed to create fileThread\n");
        return -1;
    }

    int* retVal;
    // 第二个参数用于接收线程退出码
    pthread_join(fileThreadID, (void**)&retVal);

    FILE* fp = fopen(TIME_FILENAME, "r");
    if (fp == NULL)
    {
        printf("open file error\n");
        return -2;
    }

    char buf[32] = { 0 };
    int sizeRead = fread(buf, 1, 32, fp);
    if (sizeRead == 0)
    {
        printf("read file error\n");
        return -3;
    }

    printf("Current Time is %s\n", buf);

    return 0;
}


