// emplace01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <list>

class Test
{
public:
	Test(int a, int b, int c)
	{
		ma = a;
		mb = b;
		mc = c;
		
		std::cout << "Test constructed." << std::endl;
	}

	~Test()
	{
		std::cout << "Test destructed." << std::endl;
	}

	Test(const Test& rhs)
	{
		if (this == &rhs)
		{
			return;
		}

		ma = rhs.ma;
		mb = rhs.mb;
		mc = rhs.mc;

		std::cout << "Test copy-constructed." << std::endl;
	}

private:
	int ma;
	int mb;
	int mc;
};

int main()
{
	std::list<Test> collections;
	for (int i = 0; i < 10; ++i)
	{
		Test t(1 * i, 2 * i, 3 * i);
		collections.push_back(t);
	}

	std::cout << "\n" << std::endl;
	std::list<Test> collections1;
	for (int i = 0; i < 10; ++i)
	{
		collections1.emplace_back(1 * i, 2 * i, 3 * i);
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
