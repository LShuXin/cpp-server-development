﻿// unique_ptr03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

int main()
{
    // 创建10个int类型的堆对象
    // 形式1
	std::unique_ptr<int[]> sp1(new int[10]);

	// 形式2
	std::unique_ptr<int[]> sp2;
	sp2.reset(new int[10]);

	// 形式3
	std::unique_ptr<int[]> sp3(std::make_unique<int[]>(10));

	for (int i = 0; i < 10; ++i)
	{
		sp1[i] = i;
		sp2[i] = i;
		sp3[i] = i;
	}

	for (int i = 0; i < 10; ++i)
	{
		std::cout << sp1[i] << " ," << sp2[i] << " ," << sp3[i] << std::endl;
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