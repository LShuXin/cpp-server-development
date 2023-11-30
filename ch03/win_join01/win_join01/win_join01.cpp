// win_join01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// 关于_CRT_SECURE_NO_WARNINGS 与 _CRT_SECURE_NO_DEPRECATE
// 正如大家所知，如果我们写出这样的代码：
//
// int main()
// {    
//      fopen("test.txt", "r");
// 	    return 0;
// }
//
// 在vs 2005,2008,2017下，会收到如下警告：
//
// c:"documents and settings"administrator"桌面"test"test.cpp(9) : warning C4996: 'fopen': 
// This function or variable may be unsafe. Consider using fopen_s instead. 
// To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
// 	c : "program files"microsoft visual studio 8"vc"include"stdio.h(234) : 参见“fopen”的声明
// 正如这个警告所言，产生的原因时这个方法不是安全的CRT，当然，建议使用安全的CRT，但如果不想
// 用（有时候为了安全性，得多写几行代码），要禁止这个警告 ，得定义一个宏
// #define _CRT_SECURE_NO_WARNINGS
// 一开始，我以为这个宏应该出现在fopen(当然，以及类示CRT）之间。但事实上应该是将这个宏定义在stdio.h之前。
// 也就是说，如下代码还是会报这个警告:
//
// #define _CRT_SECURE_NO_WARNINGS
// int main()
// {
//     fopen("test.txt", "r");
//     return 0;
// }
//
// 正确的做法应该是
// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>
// 问题是解决了，回过头来一想，我怎么会有这样的想法呢，这个方法本身的编译应该在调用之前嘛，
// 唉，一时糊涂。看看这个方法体的定义：
// _CRT_INSECURE_DEPRECATE(fopen_s) _CRTIMP __checkReturn FILE * __cdecl fopen(__in_z const char * _Filename, __in_z const char * _Mode);
//
// #ifndef _CRT_INSECURE_DEPRECATE
// #ifdef _CRT_SECURE_NO_WARNINGS
// #define _CRT_INSECURE_DEPRECATE(_Replacement)
// #else
// #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT("This function or variable may be unsafe. Consider using " #_Replacement " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.")
// #endif
// #endif
// 
// https://www.cnblogs.com/homeofish/archive/2009/01/15/1375988.html


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define TIME_FILENAME "time.txt"

DWORD WINAPI FileThreadFunc(LPVOID lpParameters)
{
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	char timeStr[32] = {0};
	sprintf_s(timeStr, 32, "%04d/%02d/%02d %02d:%02d:%02d",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec
		);

	// 文件不存在则创建，存在则覆盖
	FILE* fp = fopen(TIME_FILENAME, "w");
	if (fp == NULL)
	{
		printf("Failed to create %s.\n", TIME_FILENAME);
		return 1;
	}

	size_t sizeToWrite = strlen(timeStr) + 1;
	size_t ret = fwrite(timeStr, 1, sizeToWrite, fp);
	if (ret != sizeToWrite)
	{
		printf("Write file error!\n");
	}

	fclose(fp);

	return 2;
}

int main()
{
	DWORD dwFileThreadID;
	HANDLE hFileThread = CreateThread(NULL, 0, FileThreadFunc, NULL, 0, &dwFileThreadID);
	if (hFileThread == NULL)
	{
		printf("Failed to create fileThread.\n");
		return -1;
	}

	// 无限等待，直到文件线程退出，否则程序将一直挂起
	WaitForSingleObject(hFileThread, INFINITE);

	// 使用r选项，要求文件必须存在
	FILE* fp = fopen(TIME_FILENAME, "r");
	if (fp == NULL)
	{
		printf("open file error.\n");
		return -2;
	}

	char buf[32] = {0};
	int sizeRead = fread(buf, 1, 32, fp);
	if (sizeRead == 0)
	{
		printf("read file error.\n");
		fclose(fp);
		return -3;
	}

	printf("Current time is %s.\n", buf);

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
