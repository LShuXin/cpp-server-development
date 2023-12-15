// auto_ptr02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

int main()
{
	// 测试拷贝复制
	std::auto_ptr<int> sp1(new int(8));
	std::auto_ptr<int> sp2(sp1);
	if (sp1.get() != NULL)
	{
		std::cout << "sp1 is not empty" << std::endl;
	}
	else
	{
		std::cout << "sp1 is empty" << std::endl;
	}
	if (sp2.get() != NULL)
	{
		std::cout << "sp2 is not empty" << std::endl;
	}
	else
	{
		std::cout << "sp2 is empty" << std::endl;
	}

	// 测试赋值复制
	std::auto_ptr<int> sp3(new int(8));
	std::auto_ptr<int> sp4 = sp3;
	if (sp3.get() != NULL)
	{
		std::cout << "sp3 is not empty" << std::endl;
	}
	else
	{
		std::cout << "sp3 is empty" << std::endl;
	}
	if (sp4.get() != NULL)
	{
		std::cout << "sp4 is not empty" << std::endl;
	}
	else
	{
		std::cout << "sp4 is empty" << std::endl;
	}


   
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
