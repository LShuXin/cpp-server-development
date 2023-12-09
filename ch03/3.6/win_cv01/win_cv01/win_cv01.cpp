// win_cv01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <list>


class Task
{
public:
	Task(int taskID)
	{
		// 这里记住要使用this
		this->taskID = taskID;
	}

	void doTask()
	{
		std::cout << "handle a task, taskID:" << taskID << " ,threadID:" << GetCurrentThreadId() << std::endl;
	}

private:
	int taskID;
};

CRITICAL_SECTION              myCriticalSection;
CONDITION_VARIABLE            myConditionVar;
std::list<Task*>              tasks;

DWORD WINAPI consumerThread(LPVOID param)
{
    // 提前申请一个指针的内存
	Task* pTask = NULL;


	while (true)
	{
		// 进入临界区
		// 对全局任务队列的访问需要临界区保护
		EnterCriticalSection(&myCriticalSection);
		// 如果 SleepConditionVariableCS 挂起，则挂起前会离开临界区，不往下执行
		// 发生变化后，条件合适时，SleepConditionVariableCS 将直接进入临界区
		while (tasks.empty())
		{
			SleepConditionVariableCS(&myConditionVar, &myCriticalSection, INFINITE);
		}

		pTask = tasks.front();
		tasks.pop_front();
		// 为了让其它消费者线程有机会竞争，这里需要再次离开临界区
		LeaveCriticalSection(&myCriticalSection);


		if (pTask == NULL)
		{
			continue;
		}

		pTask->doTask();
		delete pTask;
		pTask = NULL;
	}

	return 0;
}



DWORD WINAPI producerThread(LPVOID param)
{

	int taskID = 0;
	Task* pTask = NULL;

	while (true)
	{
	    // 生产物品放在临界外面，因为次过程不需要临界区保护
		// 将不需要临界区保护的任务放在临界区外可以减少生产者对临界区锁的占用
		// 有利于将更多的机会让给消费者竞争锁
		pTask = new Task(taskID);
		
		// 进入临界区
		// 本案例中，只有对全局任务队列的操作才需要临界区保护
		EnterCriticalSection(&myCriticalSection);

		tasks.push_back(pTask);
		std::cout << "produce a task, taskID: " << taskID << " ,threadID: " << GetCurrentThreadId() << std::endl;

		LeaveCriticalSection(&myCriticalSection);

		// 生产商品完成之后，条件变量唤醒消费者线程
		WakeConditionVariable(&myConditionVar);

		// 自增全局唯一任务ID， 用于下一次生产
		++taskID;

		// 休眠 1 秒
		Sleep(1000);
	}

	return 0;
}


int main()
{
	InitializeCriticalSection(&myCriticalSection);
	InitializeConditionVariable(&myConditionVar);

	// 创建5个消费者线程
	HANDLE consumerThreadHandles[5];
	for (int i = 0; i < 5; ++i)
	{
		consumerThreadHandles[i] = CreateThread(NULL, 0, consumerThread, NULL, 0, NULL);
	}
	// 创建1个生产者线程
	HANDLE producerThreadHandle = CreateThread(NULL, 0, producerThread, NULL, 0, NULL);

	// 等待生产者线程退出
	WaitForSingleObject(producerThreadHandle, INFINITE);
    // 等待消费者线程退出
	for (int i = 0; i < 5; ++i)
	{
		WaitForSingleObject(consumerThreadHandles[i], INFINITE);
	}

	DeleteCriticalSection(&myCriticalSection);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
