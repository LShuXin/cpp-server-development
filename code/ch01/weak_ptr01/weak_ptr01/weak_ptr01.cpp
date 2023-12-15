// weak_ptr01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

int main()
{
    // 创建一个 shared_ptr 对象
	std::shared_ptr<int> sp1(new int(123));
	std::cout << "use count:" << sp1.use_count() << std::endl;

	// 通过构造函数获得一个 std::weak_ptr 对象
	std::weak_ptr<int> sp2(sp1);
	std::cout << "use count:" << sp1.use_count() << std::endl;

	// 通过赋值运算符得到一个std::weak_ptr 对象
	std::weak_ptr<int> sp3 = sp1;
	std::cout << "use count:" << sp1.use_count() << std::endl;

	// 通过一个std::weak_ptr 得到另一个 std::weak_ptr
	std::weak_ptr<int> sp4 = sp2;
	std::cout << "use count:" << sp1.use_count() << std::endl;

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
