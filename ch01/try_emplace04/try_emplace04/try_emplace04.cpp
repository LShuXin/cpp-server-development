﻿// try_emplace04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>
#include <memory>

class ChatDialog
{
// 其它实现省略
public:
	ChatDialog(int64_t userid):m_userid(userid)
	{
		std::cout << "ChatDialog constructor" << std::endl;
	}
	~ChatDialog()
	{
		std::cout << "ChatDialog destructor" << std::endl;
	}
	void activate()
	{
	    // 实现省略
	}
private:
	int64_t m_userid;
};

// 用于管理所有聊天对话框的map，key 是好友 id， value 是 聊天对话框对象
std::map<int64_t, ChatDialog> m_ChatDialogs;

// C++ 17 版本4
void onDoubleClickFriendItem3(int64_t userid)
{
    // 第二个 userid 是传给 ChatDialog 构造函数的参数
	auto[iter, inserted] = m_ChatDialogs.try_emplace(userid, userid);
	iter->second.activate();
}


int main()
{
    // 测试用例
    // 906106443
	onDoubleClickFriendItem3(906106443L);

    // 906106444
	onDoubleClickFriendItem3(906106444L);

	// 906106443
	onDoubleClickFriendItem3(906106443L);
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
