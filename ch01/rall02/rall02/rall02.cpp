// rall02.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <winsock2.h>
#include <stdio.h>

// 链接 Windows 的 socket 库
#pragma comment(lib, "ws2_32.lib")

int main()
{
    // 注意，由于 goto 语句不能跳过变量定义，所以在这里提前定义下文需要用到的变量
	SOCKET sockSrv;
	SOCKADDR_IN addrSrv;
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);
	char msg[] = "HelloWorld";

	// 初始化 socket 库
	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return 1;
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		goto cleanup2;
	}

	// 创建用于监听的 socket
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == -1)
	{
		goto cleanup2;
	}

	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	// 绑定 socket，监听 6000 端口
	if (bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1)
	{
		goto cleanup1;
	}

	// 启动监听，准备接受客户端的连接请求
	if (listen(sockSrv, 15) == -1)
	{
		goto cleanup1;
	}

	while (true) 
	{
	    // 等待客户端请求的到来，如果有客户端连接，则接受连接
		SOCKET socketClient = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		if (socketClient == -1)
		{
			break;
		}

		// 向客户端发送 “HelloWorld”消息
		send(socketClient, msg, strlen(msg), 0);
		closesocket(socketClient);
	} // end while-loop


	
cleanup1:
	closesocket(sockSrv);

cleanup2:
	WSACleanup();

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
