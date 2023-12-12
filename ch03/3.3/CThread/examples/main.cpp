#include <iostream>
#include "CThread.h"


class MyThread : public CThread
{
    void Run() override
    {
        unsigned long long loopCnt = 0;
        unsigned long long maxLoopCnt = 10;
        while (true)
        {
            SleepMS(1000);
            ++loopCnt;
            std::cout << "Custom thread running, loopCnt:" << loopCnt << std::endl;
            if (loopCnt >= maxLoopCnt)
            {
                break;
            }
        }
    }
};

int main()
{

    MyThread myThread;
    myThread.Create();
    myThread.Join();

    return 0;
}

