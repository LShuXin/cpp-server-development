// structured_bind.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <map>


struct UserInfo
{
	std::string username;
	std::string password;
	int gender;
	int age;
	std::string address;
};

struct Point
{
	double x;
	double y;
};


// 运行该示例需要 C++17
int main()
{
	std::map<std::string, int> cities;
	cities["beijing"] = 0;
	cities["shanghai"] = 1;
	cities["shenzhen"] = 2;
	cities["guangzhou"] = 3;

	//for (const auto& [key, value] : cities)
	// {
	// 	std::cout << key << ":" << value << std::endl;
	// }

	// 这一行在 C++11 之前的写法太麻烦了
	// std::pair<std::map<std::string, int>::iterator, int> insertResult = cities.insert(std::pair<std::string, int>({ "shanghai", 2 }));
	// std::cout << insertResult.second << std::endl;

	// 在c++11 中写成
	auto insertResult = cities.insert(std::pair<std::string, int>({ "shanghai", 2 }));
	std::cout << "Is insertion successfull? " << (insertResult.second ? "true" : "false")
		<< ", element key:" << insertResult.first->first << " vlaue:" << insertResult.first->second << std::endl;


	std::cout << std::endl;
	UserInfo userInfo = {
	  "Tom",
	  "123456",
	  0,
	  25,
	  "pudong street"
	};
	std::string username = userInfo.username;
	std::string password = userInfo.password;
	int gender = userInfo.gender;
	int age = userInfo.age;
	std::string address = userInfo.address;


	std::cout << std::endl;
	std::tuple<std::string, std::string, int, int, std::string> userInfo1 =
	{ "Tom", "123456", 0, 25, "pudong street" };

	// 或
	//std::tuple<std::string, std::string, int, int, std::string> userInfo2("Tom", "123456", 0, 25, "pudong street");

	std::string username1 = std::get<0>(userInfo1);
	std::string password1 = std::get<1>(userInfo1);
	int gender1 = std::get<2>(userInfo1);
	int age1 = std::get<3>(userInfo1);
	std::string address1 = std::get<4>(userInfo1);
	std::cout << username1 << " " << password1 << " " << gender1 << " " << age1 << " " << address1 << std::endl;


	std::cout << std::endl;
	double myArray[3] = { 1.0, 2.0, 3.0 };
	auto [a, b, c] = myArray;
	// 书本中为 Point myPoint(10.0, 20.0);
	Point myPoint{ 10.0, 20.0 };
	auto [myX, myY] = myPoint;


    
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
