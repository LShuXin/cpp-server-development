// win_event02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <Windows.h>

bool g_bTaskCompleted = false;
std::string g_TaskResult;
HANDLE g_hTaskEvent = NULL;

DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
    // 使用 Sleep 函数模拟 1 个很耗时的操作
	Sleep(3000);
	g_TaskResult = "task completed";
	g_bTaskCompleted = true;

	// 设置事件信号
	SetEvent(g_hTaskEvent);

	return 0;
}

int main()
{
    // 创建一个匿名的手动重置初始无信号的事件对象
	g_hTaskEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE hWorderThread = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);

	DWORD dwResult = WaitForSingleObject(g_hTaskEvent, INFINITE);
	if (dwResult == WAIT_OBJECT_0)
	{
		std::cout << g_TaskResult << std::endl;
	}

	CloseHandle(hWorderThread);
	CloseHandle(g_hTaskEvent);

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
