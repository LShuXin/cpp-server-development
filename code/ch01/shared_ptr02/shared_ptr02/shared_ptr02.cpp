// shared_ptr02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <memory>

class A
{
public:
	A()
	{
		std::cout << "A constructor" << std::endl;
	}
	~A()
	{
		std::cout << "A destructor" << std::endl;
	}

};

int main()
{
	{
	    // 初始化方式1
		// 在 sp1 构造时触发对象 A 的构造，因此 A 的构造函数被执行
		// 此时只有一个 sp1 对象引用新建的A对象（下面统称为资源对象A）
		// 因此打印出来的引用计数值为1
		std::shared_ptr<A> sp1(new A());
		std::cout << "use count:" << sp1.use_count() << std::endl;

		// 初始化方式2
		// 利用sp1拷贝一份sp2，导致打印出来的引用计数值为2
		std::shared_ptr<A> sp2(sp1);
		std::cout << "use count:" << sp1.use_count() << std::endl;

		// 调用sp2的reset方法，sp2释放对资源A的引用
		// 因此打印出来的引用计数值再次变为1
		sp2.reset();
		std::cout << "use count:" << sp1.use_count() << std::endl;

		{
		    // 利用sp1再次创建sp3， 因此打印出来的引用计数为2
			std::shared_ptr<A> sp3(sp1);
			std::cout << "use count:" << sp1.use_count() << std::endl;
		}

		// 程序执行到这里，sp3 因出了其作用域被析构
		// 资源 A 的引用计数减1， 因此接下来打印的引用计数为1
		std::cout << "use count:" << sp1.use_count() << std::endl;
	}

	// 在这里，sp1 出了其作用域被析构，在其析构时递减资源A的引用计数到0，并析构资源A对象
	// 因此类A的析构函数被调用

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
