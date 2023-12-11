// win_wait.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

#define TIME_FILENAME "time.txt"

DWORD WINAPI FileThreadFunc(LPVOID lpParameter)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	char timeStr[32] = { 0 };
	snprintf(timeStr, 32, "%04d-%02d-%02d %02d:%02d:%02d",
		t->tm_year + 1900,
		t->tm_mon,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec
		);

	FILE* fp = fopen(TIME_FILENAME, "w");
	if (fp == NULL)
	{
		printf("Failed to create time.txt\n");
		return -1;
	}

	size_t sizeToWrite = strlen(timeStr) + 1;
	size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
	if (ret != sizeToWrite)
	{
		printf("Failed to write file\n");
		return -2;
	}

	fclose(fp);
	return 0;
}


int main()
{
	DWORD dwFileThreadID;
	HANDLE hFileThread = CreateThread(NULL, 0, FileThreadFunc, NULL, 0, &dwFileThreadID);

	if (hFileThread == NULL)
	{
		printf("Failed to create fileThread\n");
		return -1;
	}

	// 无限等待，直到文件线程退出，否则主线程一直挂起
	WaitForSingleObject(hFileThread, INFINITE);

	FILE* fp = fopen(TIME_FILENAME, "r");
	if (fp == NULL)
	{
		printf("open file error\n");
		return -2;
	}

	char buf[32] = { 0 };
	size_t ret = fread(buf, 1, 32, fp);
	if (ret == 0)
	{
		printf("read file error\n");
		fclose(fp);
		return -3;
	}

	printf("Current Time is: %s", buf);

	fclose(fp);

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
