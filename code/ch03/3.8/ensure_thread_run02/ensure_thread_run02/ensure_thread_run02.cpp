// ensure_thread_run02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>

std::vector<std::shared_ptr<std::thread>>    spWorkThreads;
bool                                       success = false;
std::mutex                                 mutex;
std::condition_variable                    mycv;

void* thread_func(int id)
{
	{
		std::unique_lock<std::mutex>       lock(mutex);
		success = true;
		std::cout << "thread NO." << id << " has been working" << std::endl;
		mycv.notify_all();
	}

	// 下面是工作内容
	while (true)
	{

	}

	return NULL;
}

int main()
{
	for (int i = 0; i < 5; ++i)
	{
		success = false;
		std::shared_ptr<std::thread> spThread;
		spThread.reset(new std::thread(thread_func, i));

		{
			std::unique_lock<std::mutex> guard(mutex);
			while (!success)
			{
				mycv.wait(guard);
			}
		}

		std::cout << "thread " << i << " create success" << std::endl;

		spWorkThreads.push_back(spThread);
	}

	for (auto& thread : spWorkThreads)
	{
		thread->join();
	}

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
