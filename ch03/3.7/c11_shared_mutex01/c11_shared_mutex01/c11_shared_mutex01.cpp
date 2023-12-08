// c11_shared_mutex01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>

// 读线程数量
#define READ_THREAD_COUNT 8
// 最大循环次数
#define LOOP_COUNT        5000000



class SharedMutexCounter
{
public:
	SharedMutexCounter() = default;
	~SharedMutexCounter() = default;

	// std::shared_mutex 的 std::shared_lock
	// 可以让多个线程同时读
	unsigned int get() const {
	    // 注意，使用的是 std::shared_mutex 的 std::shared_lock
		std::shared_lock<std::shared_mutex> lock(m_mutex);
		return m_value;
	}

    // std::shared_mutex 的 std::unique_lock
	// 某一时刻只能让一个线程写
	void increment()
	{
	    // 注意，使用的是 std::shared_mutex 的 std::unique_lock
		std::unique_lock<std::shared_mutex> locl(m_mutex);
		++m_value;
	}

	// std::shared_mutex 的 std::unique_lock
	// 同一时刻只能让一个线程写
	void reset()
	{
	    // 注意，是 std::shared_mutex 的 std::unique_lock
		std::unique_lock<std::shared_mutex> lock(m_mutex);
		m_value = 0;
	}

private:
	mutable std::shared_mutex       m_mutex;
	unsigned int                    m_value;    // 多个线程的共享资源
};


class MutexCounter
{
public:
	MutexCounter() = default;
	~MutexCounter() = default;
	// std::mutex 的 std::unique_lock
	// 只能让单个线程读
	unsigned int get() const {
	    // 注意，是  std::mutex 的 std::unique_lock
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_value;
	}

	// std::mutex  的 std::unique_lock
	// 只能让同一个线程写
	void increment()
	{
	    // 注意，是 std::mutex 的 std::unique_lock
		std::unique_lock<std::mutex> lock(m_mutex);
		++m_value;
	}

private:
	mutable std::mutex   m_mutex;
	unsigned int         m_value;  // 多个线程的共享资源
};


// 测试 SharedMutexCounter
void testSharedMutexCounter()
{
	SharedMutexCounter counter;
	unsigned int temp;

	auto reader = [&counter, &temp]() {
		for (int i = 0; i < LOOP_COUNT; ++i)
		{
			temp = counter.get();
		}
	};

	auto writer = [&counter]() {
		for (int i = 0; i < LOOP_COUNT; ++i)
		{
			counter.increment();
		}
	};


	// 存放读线程对象指针的数组
	std::thread** tarray = new std::thread* [READ_THREAD_COUNT];


	clock_t beg = clock();

	for (int i = 0; i < READ_THREAD_COUNT; ++i)
	{
		tarray[i] = new std::thread(reader);
	}
	std::thread wThread(writer);

	for (int i = 0; i < READ_THREAD_COUNT; ++i)
	{
		tarray[i]->join();
	}
	wThread.join();

	clock_t end = clock();

	std::cout << "[test_shared_mutex]:" << std::endl;
	std::cout << "thread count: " << READ_THREAD_COUNT << std::endl;
	std::cout << "result: " << counter.get() << " cost: " << end - beg << " temp: " << temp << std::endl;


}

void testMutexCounter()
{
	unsigned int temp = 0;
	MutexCounter counter;

	auto reader = [&counter, &temp]() {
		for (int i = 0; i < LOOP_COUNT; ++i)
		{
			temp = counter.get();
		}
	};

	auto writer = [&counter]() {
		for (int i = 0; i < LOOP_COUNT; ++i) {
			counter.increment();
		}
	};

	// 存放读线程对象指针的数组
	std::thread** tarray = new std::thread* [READ_THREAD_COUNT];


	clock_t beg = clock();
	for (int i = 0; i < READ_THREAD_COUNT; ++i)
	{
		tarray[i] = new std::thread(reader);
	}
	std::thread wThread(writer);

	for (int i = 0; i < READ_THREAD_COUNT; ++i)
	{
		tarray[i]->join();
	}
	wThread.join();

	clock_t end = clock();

	std::cout << "[testMutexCounter]:" << std::endl;
	std::cout << "thread count: " << READ_THREAD_COUNT << std::endl;
	std::cout << "result: " << counter.get() << ",cost: " << end - beg << ", temp: " << temp << std::endl;
}


int main()
{
	// testSharedMutexCounter();
	testMutexCounter();
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
