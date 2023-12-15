// c11_cv.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <condition_variable>
#include <list>
#include <chrono>

class Task
{
public:
	Task(int taskID)
	{
		this->taskID = taskID;
	}

	void doTask()
	{
		std::cout << "handle task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl;
	}

private:
	int taskID;
};

std::mutex                    mymutex;
std::condition_variable       mycv;
std::list<Task*>              tasks;


void* consumer_thread()
{
	Task* pTask = NULL;

	while (true)
	{
		// 增加一个作用域，减小锁的作用范围
		{
			std::unique_lock<std::mutex> guard(mymutex);

			// 如果获得了互斥锁，但是条件不合适
			// 则 pthread_cond_wait 会释放锁，不向下执行
			// 发生变化后， 如果条件合适，pthread_cond_wait 会直接获得锁
			while (tasks.empty())
			{
				mycv.wait(guard);
			}
			pTask = tasks.front();
			tasks.pop_front();
		}

		if (pTask == NULL)
		{
			continue;
		}
		pTask->doTask();
		delete pTask;
		pTask = NULL;
	}

	return NULL;
}

void* producer_thread()
{
	int taskID = 0;
    // 提前定义，避免在 while 中重复定义
	Task* pTask = NULL;

	while (true)
	{
		// 这一步不需要放在临界区中
		pTask = new Task(taskID);

		// 作用域减小锁的作用范围
		{
			std::unique_lock<std::mutex> guard(mymutex);
			tasks.push_back(pTask);
			std::cout << "produce a task, taskID: " << taskID << ", threadID: " << std::this_thread::get_id() << std::endl;
		}

		// 释放信号量，唤醒一个消费者线程
		mycv.notify_one();

		++taskID;
		pTask = NULL;

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return NULL;
}


int main()
{
	std::thread consumerThread1(consumer_thread);
	std::thread consumerThread2(consumer_thread);
	std::thread consumerThread3(consumer_thread);
	std::thread consumerThread4(consumer_thread);
	std::thread consumerThread5(consumer_thread);

	std::thread producerThread(producer_thread);

	producerThread.join();
	consumerThread1.join();
	consumerThread2.join();
	consumerThread3.join();
	consumerThread4.join();
	consumerThread5.join();

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
