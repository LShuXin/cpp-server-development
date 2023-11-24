// rall04.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <winsock2.h>
#include <stdio.h>
#include <Ws2tcpip.h>
#include <tchar.h>

// 链接 Windows 的 socket 网络库
#pragma comment(lib, "ws2_32.lib")

class ServerSocket
{
public:
	ServerSocket()
	{
		m_bInit = false;
		m_ListenSocket = -1;
	}

	~ServerSocket()
	{
		if (m_ListenSocket != -1)
		{
			::closesocket(m_ListenSocket);
		}

		if (m_bInit)
		{
			::WSACleanup();
		}
	}

	bool DoInit()
	{
		// 初始化 socket 库
		WORD wVersionRequested = MAKEWORD(2, 2);
		WSAData wsaData;
		int err = ::WSAStartup(wVersionRequested, &wsaData);
		if (err != 0)
		{
			return false;
		}

		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			return false;
		}

		m_bInit = true;

		// 创建用于监听的 socket
		m_ListenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
		if (m_ListenSocket == -1)
		{
			return false;
		}

		return true;
	}

	bool DoBind(const char* ip, short port = 6000)
	{
		SOCKADDR_IN addrSrv;
	        // Windows10 EnterPrise + Visual Stuido 2017 Community 运行此代码时发生如下错误：
		// 
		// E1097 未知特性 "no_init_all"	rall04	C : \Program Files(x86)\Windows Kits\10\Include\10.0.18362.0\um\winnt.h	7597
		//
		// 解决方案：
		// 在 winnt.h 头文件中
		// 
                // #if (_MSC_VER >= 1915)
		// #pragma warning(disable:4845)   // __declspec(no_init_all) used but d1initall not set
		// #endif
		// 
		// 之后添加
		//
		// #if (_MSC_VER >= 1915)
		// #define no_init_all deprecated
		// #endif
		//
		// 即可解决
		// 
		// 值得一提的是
		//
	        // #if (_MSC_VER >= 1915)
		// #pragma warning(disable:4845)   // __declspec(no_init_all) used but d1initall not set
		// #endif
		//
		// 这一代码块是微软工程师用于在旧版本的 vs 中消除该错误提示的预编译头
		// 虽然微软的工程师们宣称他们在最新的 vs2019 中修复了该错误， 但是仍有很多人收到了该错误的困扰
		//
		// 有关参考链接：
		// https://blog.csdn.net/Elegies/article/details/102642022
		// https://forum.openframeworks.cc/t/e1097-unknown-attribute-no-init-all-in-winnt-h/35808
		// https://developercommunity.visualstudio.com/content/problem/539919/e1097-unknown-attribute-no-init-all-in-winnth-in-w.html

		
		// 使用 addrSrv.sin_addr.S_un.S_addr = inet_addr(ip); 会发生如下错误：
		// C4996 'inet_addr': Use inet_pton() or InetPton() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings
		//
		// 解决方案一(需要引入 Ws2tcpip.h)：
		// inet_pton(AF_INET, "0.0.0.0", &addrSrv.sin_addr.S_un.S_addr);
		//
		// 解决方案二(需要引入 Ws2tcpip.h、tchar.h)：
		// InetPton(AF_INET, _T("0.0.0.0"), &addrSrv.sin_addr.S_un.S_addr);
		//
		// 解决方案三：
		// 添加 #pragma warning(disable:4996)
		//
		// 相关链接： https://stackoverflow.com/questions/36683785/inet-addr-use-inet-pton-or-inetpton-instead-or-define-winsock-deprecated


		// 方案一
		// inet_pton(AF_INET, "0.0.0.0", &addrSrv.sin_addr.S_un.S_addr);

		// 方案二
		// InetPton(AF_INET, _T("0.0.0.0"), &addrSrv.sin_addr.S_un.S_addr);

		// 方案三
                #pragma warning(disable:4996) 
		addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);

		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(port);
		if (::bind(m_ListenSocket, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR)) == -1)
		{
			return false;
		}

		return true;
	}

	bool DoListen(int backLog = 15)
	{
		if (::listen(m_ListenSocket, backLog) == -1)
		{
			return false;
	    }

		return true;
	}

	bool DoAccept()
	{
		SOCKADDR_IN addrClient;
		int len = sizeof(SOCKADDR);
		char msg[] = "HelloWorld";
		while (true)
		{
			// 等待客户端的请求到来，如果有客户端连接，则接受连接
			SOCKET socketClient = ::accept(m_ListenSocket, (SOCKADDR*)&addrClient, &len);
			if (socketClient == -1)
			{
				break;
			}

			// 向客户端发送 “HelloWorld" 消息
			::send(socketClient, msg, strlen(msg), 0);
			::closesocket(socketClient);
		} // end inner-while-loop

		return false;
	}

private:
	bool m_bInit;
	SOCKET m_ListenSocket;
};

int main()
{
	ServerSocket serverSocket;
	if (!serverSocket.DoInit()) 
	{
		return false;
	}

	if (!serverSocket.DoBind("0.0.0.0", 6000))
	{
		return false;
	}


	if (!serverSocket.DoListen(15))
	{
		return false;
	}

	if (!serverSocket.DoAccept())
	{
		return false;
	}

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
