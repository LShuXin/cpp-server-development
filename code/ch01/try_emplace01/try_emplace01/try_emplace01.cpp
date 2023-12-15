// try_emplace01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>

class ChatDialog
{
// 其它实现省略
public:
	void activate()
	{
	    // 实现省略
	}

};


// 用于管理所有聊天对话框的map，key 是好友id,value 是聊天对话框指针 ChagtDilog*
std::map<int64_t, ChatDialog*> m_ChatDialogs;

// 普通版本
void onDoubleClickFriendItem(int64_t userid)
{
	auto targetChatDialog = m_ChatDialogs.find(userid);
	// 好友对对话框不存在，创建它并激活
	if (targetChatDialog == m_ChatDialogs.end())
	{
		ChatDialog* pChatDialog = new ChatDialog();
		m_ChatDialogs.insert(std::pair<int64_t, ChatDialog*>(userid, pChatDialog));
		pChatDialog->activate();
	}
	// 好友对话框存在，直接激活
	else
	{
		targetChatDialog->second->activate();
	}
}

// C++17 版本1
void onDoubleClickFriendItem2(int64_t userid)
{
    // 结构化绑定和try_emplace都是C++17语法
	auto [iter, inserted] = m_ChatDialogs.try_emplace(userid);
	if (inserted)
	{
		iter->second = new ChatDialog();
	}

	iter->second->activate();
}

int main()
{
    // 测试用例
	// 906106643是userid
	onDoubleClickFriendItem2(906106643L);
	
	// 906106644是userid
	onDoubleClickFriendItem2(906106644L);

	// 906106643是userid
	onDoubleClickFriendItem2(906106643L);

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
