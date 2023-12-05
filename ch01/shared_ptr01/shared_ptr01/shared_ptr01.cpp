﻿// shared_ptr01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

int main()
{
    // 初始化方式1
	std::shared_ptr<int> sp1(new int(123));
	std::cout << *sp1.get() << std::endl;

	// 初始化方式2
	std::shared_ptr<int> sp2;
	sp2.reset(new int(123));
	std::cout << *sp2.get() << std::endl;

	// 初始化方式3
	std::shared_ptr<int> sp3;
	sp3 = std::make_shared<int>(123);
	std::cout << *sp3.get() << std::endl;
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
