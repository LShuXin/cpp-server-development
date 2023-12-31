﻿// auto_usage.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <string>

int main()
{
	std::map<std::string, std::string> seasons;
	seasons["spring"] = "123";
	seasons["summer"] = "456";
	seasons["autumn"] = "789";
	seasons["winter"] = "101112";

	// for (std::map<std::string, std::string>::iterator iter = seasons.begin(); iter != seasons.end(); ++iter)
	for (std::map<std::string, std::string>::const_iterator iter = seasons.begin(); iter != seasons.end(); ++iter)
	{
		// 要包含 std::string 否则会报错：
		// E0349	没有与这些操作数匹配的 "<<" 运算符	auto_usage	
	    // 操作数类型为:  std::ostream << std::string
		std::cout << iter->second << std::endl;
	}

	for (auto iter = seasons.begin(); iter != seasons.end(); ++iter)
	{
		std::cout << iter->second << std::endl;
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
