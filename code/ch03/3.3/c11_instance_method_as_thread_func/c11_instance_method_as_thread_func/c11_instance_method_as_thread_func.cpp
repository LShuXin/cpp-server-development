// c11_instance_method_as_thread_func.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <memory>

class Thread
{
public:
	Thread()
	{
	}
	
	~Thread()
	{
	}

	void Start()
	{
		m_stopped = false;
		// threadFunc 是类的非静态方法
		// 所以作为线程函数，第一个参数必须传递类实例的地址，即 this 指针
		m_spThread.reset(new std::thread(&Thread::threadFunc, this, 8888, 9999));
	}

	void Stop()
	{
		m_stopped = true;
		if (m_spThread)
		{
			if (m_spThread->joinable())
			{
				m_spThread->join();
			}
		}
	}
private:
	void threadFunc(int arg1, int arg2)
	{
		while (!m_stopped)
		{
			std::cout << "Thread function use private instance method." << std::endl;
		}
	}

private:
	std::shared_ptr<std::thread>         m_spThread;
	bool                                 m_stopped;
};

int main()
{
	Thread thread;
	thread.Start();

	// 权宜之计，不让主线程退出
	while (true)
	{

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
