// c11_mutex01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

// g_num 用 g_num_mutex 进行保护
int                    g_num = 0;
std::mutex             g_num_mutex;

void slow_increment(int id)
{
	for (int i = 0; i < 3; ++i)
	{
		g_num_mutex.lock();
		
		++g_num;
		std::cout << id << " => " << g_num << std::endl;
	
		g_num_mutex.unlock();


		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


int main()
{
	std::thread t1(slow_increment, 0);
	std::thread t2(slow_increment, 1);

	t1.join();
	t2.join();

	return  0;
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
