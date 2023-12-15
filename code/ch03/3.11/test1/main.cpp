#include <time.h>
#include <stdio.h>

int main()
{
    time_t tNow = time(NULL);
    time_t tEnd = tNow + 1800;

    struct tm* ptmNow = localtime(&tNow);
    struct tm* ptmEnd = localtime(&tEnd);

    char szNow[50] = {0};
    char szEnd[50] = {0};
    
    strftime(szNow, 50, "%H:%M:%S", ptmNow);
    strftime(szEnd, 50, "%H:%M:%S", ptmEnd);

    printf("%s\n", szNow);
    printf("%s\n", szEnd);

    return 0;
}


