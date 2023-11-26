#pragma once
// 网络通信的基础类

#include <WinSock2.h>
#include <iostream>
#include <string.h>

class CNetProxy;

class CSocketClient
{
public:
	CSocketClient();
	~CSocketClient();

public:
	void test();

	void SetProxyWnd(HWND hProxyWnd);

	bool Init(CNetProxy* pNetProxy);
	bool Uninit();

	int Register(const char* pszUser, const char* pszPassword);
	void GuestLogin();

	BOOL isClosed();
	BOOL Connect(int timeout = 3);
	void AddData(int cmd, const std::string& strBuffer);
	void AddData(int cmd, const char* pszBuff, int nBuffLen);
	void Close();

	BOOL ConnectServer(int timeout = 3);
	BOOL SendLoginMsg();
	BOOL RecvLoginMsg(int& nRet);
	BOOL LLogin(int& nRet);

private:
	void LoadConfig();
	static UINT CALLBACK SendDataThreadProc(LPVOID lpParam);
	static UINT CALLBACK RecvDataThreadProc(LPVOID lpParam);
	bool Send();
	bool Recv();
	bool CheckRecivedData();
	void SendHeartbeatPackage();


private:
	// 这里暴露了太多与实现细节相关的成员对象
	SOCKET m_hSocket;
	short m_nPort;
	char m_szServer[64];
	long m_nLastDataTime;
	long m_nHeartbeatInterval;
	CRITICAL_SECTION m_csLastDataTime;
	HANDLE m_hSendDataThread;
	HANDLE m_hRecvDataThread;
};