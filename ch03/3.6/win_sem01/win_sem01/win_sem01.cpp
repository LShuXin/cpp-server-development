// win_sem01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <list>
#include <time.h>
#include <string>

HANDLE g_hMsgSemaphore = NULL;
std::list<std::string> g_listChatMsg;
// 保护 g_listChatMsg 的临界区对象
CRITICAL_SECTION       g_csMsg;


DWORD __stdcall NetThreadProc(LPVOID lpThreadParameter)
{
	int nMsgIndex = 0;
	while (true)
	{
		EnterCriticalSection(&g_csMsg);
		// 随机产生1~4条消息
		int count = rand() % 4 + 1;
		for (int i = 0; i < count; i++)
		{
			nMsgIndex++;
			SYSTEMTIME st;
			GetLocalTime(&st);
			char szChatMsg[64] = {0};
			sprintf_s(szChatMsg,
				64,
				"[%04d-%02d-%02d %02d:%02d:%02d] A new msg, NO.%d.",
				st.wYear,
				st.wMonth + 1,
				st.wDay,
				st.wHour,
				st.wMinute,
				st.wSecond,
				nMsgIndex
				);
			g_listChatMsg.push_back(szChatMsg);
		}
		LeaveCriticalSection(&g_csMsg);

		//  增加 count 个资源数量
		ReleaseSemaphore(g_hMsgSemaphore, count, NULL);

		Sleep(1000);
	}

	return NULL;
}

DWORD __stdcall ParseThreadProc(LPVOID lpThreadParameter)
{
	DWORD dwThreadID = GetCurrentThreadId();

	std::string current;
	while (true)
	{
		if (WaitForSingleObject(g_hMsgSemaphore, INFINITE) == WAIT_OBJECT_0)
		{
			EnterCriticalSection(&g_csMsg);
			if (!g_listChatMsg.empty())
			{
				current = g_listChatMsg.front();
				g_listChatMsg.pop_front();
				std::cout << "Thread: " << dwThreadID << " parse msg: " << current << std::endl;
			}
			LeaveCriticalSection(&g_csMsg);
		}
	}

	return 0;
}


int main()
{
   // 初始化随机数种子
	srand(time(NULL));
	InitializeCriticalSection(&g_csMsg);

	// 创建一个匿名的 semaphore 对象，初始资源数量为0
	g_hMsgSemaphore = CreateSemaphore(NULL, 0, INT_MAX, NULL);

	HANDLE hNetThread = CreateThread(NULL, 0, NetThreadProc, NULL, 0, NULL);
	HANDLE hWorkerThreads[4];
	for (int i = 0; i < 4; ++i)
	{
		hWorkerThreads[i] = CreateThread(NULL, 0, ParseThreadProc, NULL, 0, NULL);
	}

	for (int i = 0; i < 4; ++i)
	{
		WaitForSingleObject(hWorkerThreads[i], INFINITE);
		CloseHandle(hWorkerThreads[i]);
	}

	WaitForSingleObject(hNetThread, INFINITE);

	CloseHandle(hNetThread);
	CloseHandle(g_hMsgSemaphore);
	DeleteCriticalSection(&g_csMsg);

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
