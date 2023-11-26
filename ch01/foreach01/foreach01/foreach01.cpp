// foreach01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <string>
#include <vector>


class A 
{
public:
	A()
	{
	
	}

	~A() = default;

	A(const A& rhs)
	{
		std::cout << "A 的拷贝构造函数被执行" << std::endl;
	}

public:
	int m;

};

int main()
{
	int arr[3] = { 1, 2, 3 };
	
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		std::cout << arr[i] << std::endl;
	}

	
	std::cout << std::endl;
	for (int i : arr)
	{
		std::cout << i << std::endl;
	}

	std::cout << std::endl;
	for (auto i : arr)
	{
		std::cout << i << std::endl;
	}

	std::cout << std::endl;
	for (int& i : arr)
	{
		i *= i;
	}
	for (int& i : arr)
	{
		std::cout << i << std::endl;
	}

	std::map<std::string, std::string> seasons;
	seasons["spring"] = "123";
	seasons["summer"] = "456";
	seasons["autumn"] = "789";
	seasons["winter"] = "101112";
	for (auto iter : seasons)
	{
		// 注意，不是 std::cout << iter->second << std::endl;
		std::cout << iter.second << std::endl;
	}


	std::cout << std::endl;
	std::vector<std::string> v;
	v.push_back("zhangsan");
	v.push_back("lisi");
	v.push_back("maowu");
	v.push_back("maliu");
	for (auto iter : v)
	{
		// 简单的数据类型，iter 是原数据的拷贝，所以这里不会修改原数组
		iter = "hello";
	}
	for (auto iter : v)
	{
		std::cout << iter << std::endl;
	}

	std::cout << std::endl;
	// 实际上可以通过这种方式修改
	for (std::string& iter : v)
	{
		iter = "Hello";
	}
	for (auto iter : v)
	{
		std::cout << iter << std::endl;
	}

	std::cout << std::endl;
	A a1;
	A a2;
	std::vector<A> v1;
	v1.push_back(a1);
	v1.push_back(a2);

	std::cout << std::endl;
	for (auto iter : v1)
	{
		// 在每一轮循环当中， iter 都是 v1 中元素的拷贝(通过调用 A 的拷贝构造函数生成)
	    // 因此无法改变原数组的值
		// 实际使用 for-each 循环的时候应该尽量使用 v1 中元素的引用，减少不必要的构造函数调用开销
		iter.m = 9;
	}
     
	std::cout << std::endl;
	for (auto iter : v1)
	{
		// 这里打印出来是随机值，并不是上面的9
		std::cout << iter.m << std::endl;
	}

	std::cout << std::endl;
	// 可以通过下面的方式修改
	for (A& iter : v1)
	{
		iter.m = 10;
	}
	for (const A& iter : v1)
	{
		std::cout << iter.m << std::endl;
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
