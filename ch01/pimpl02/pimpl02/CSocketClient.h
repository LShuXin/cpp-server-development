// 网络通信的基础类

#include <WinSock2.h>
#include <iostream>

class CNetProxy;

class CSocketClient{
public:
	CSocketClient();
	~CSocketClient();

public:
	void test();

	void setProxyWnd(HWND hProxyWnd);

	bool Init(CNetProxy* pNetProxy);
	bool Uninit();

	int Register(const char* pszUser, const char* pszPassword);
	void GuestLogin();

	BOOL IsClosed();
	BOOL Connect(int timeout = 3);
	void AddData(int cmd, const std::string& strBuffer);
	void AddData(int cmd, const char* pszBuff, int mBufferLen);
	void Close();

	BOOL ConnectServer(int timeout = 3);
	BOOL SendLoginMsg();
	BOOL RecvLoginMsg(int& nRet);
	BOOL Login(int& nRet);

private:
	class Impl;
	Impl* m_pImpl;

};

