// win_mutex01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <string>

HANDLE g_hMutex;
int    g_iResource = 0;

DWORD __stdcall WorkerThreadProc(LPVOID lpThreadParameter)
{
	DWORD dwThreadID = GetCurrentThreadId();

	while (true)
	{
		if (WaitForSingleObject(g_hMutex, 1000) == WAIT_OBJECT_0)
		{
			g_iResource++;
			std::cout << "Thread: " << dwThreadID << " becomes mutex owner, ResourceNO: " << g_iResource << std::endl;
			ReleaseMutex(g_hMutex);
		}

		Sleep(1000);
	}

	return 0;
}


int main()
{
    // 创建一个匿名的 Mutex 对象并设置在默认情况下主线程不会拥有该线程
	g_hMutex = CreateMutex(NULL, false, NULL);

	HANDLE hWorkerThreads[5];
	for (int i = 0; i < 5; ++i)
	{
		hWorkerThreads[i] = CreateThread(NULL, 0, WorkerThreadProc, NULL, 0, NULL);
	}

	for (int i = 0; i < 5; ++i)
	{
		// 等待工作线程退出
		WaitForSingleObject(hWorkerThreads[i], INFINITE);
		CloseHandle(hWorkerThreads[i]);
	}

	CloseHandle(g_hMutex);

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
