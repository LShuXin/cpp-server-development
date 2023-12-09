// win_criticalsection01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <list>
#include <iostream>
#include <string>

CRITICAL_SECTION                  g_cs;
int                               g_number = 0;

DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
	DWORD dwThreadID = GetCurrentThreadId();

	while (true)
	{
		EnterCriticalSection(&g_cs);
		std::cout << "Enter CriticalSection, ThreadID: " << dwThreadID << std::endl;
		g_number++;
		SYSTEMTIME st;
		// 获取当前系统时间
		GetLocalTime(&st);
		char szMsg[64] = { 0 };
		sprintf(szMsg,
			"[%04d-%02d-%02d %02d:%02d:%02d] NO.%d, ThreadID: %d",
			st.wYear,
			st.wMonth + 1,
			st.wDay,
			st.wHour,
			st.wMinute,
			st.wSecond,
			g_number,
			dwThreadID
		);

		std::cout << szMsg << std::endl;
		std::cout << "Leave CriticalSection, ThreadID: " << dwThreadID << std::endl;
		LeaveCriticalSection(&g_cs);


		// 睡眠1秒
		Sleep(1000);
	}

	return 0;
}

int main()
{
	InitializeCriticalSection(&g_cs);
	HANDLE hWorkerThread1 = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);
	HANDLE hWorkerThread2 = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);

	WaitForSingleObject(hWorkerThread1, INFINITE);
	WaitForSingleObject(hWorkerThread2, INFINITE);

	// 关闭线程句柄
	CloseHandle(hWorkerThread1);
	CloseHandle(hWorkerThread2);

	DeleteCriticalSection(&g_cs);

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
