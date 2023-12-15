#include "CSocketClient.h"

// 这里类 Impl 的定义要放在 CSocketClient 构造函数定义之前
// 因为 CSocketClient 构造函数的定义中用到了 Impl 类
struct CSocketClient::Impl
{
public:
	Impl()
	{
		// TODO: 可以在这里对成员变量做一些初始化操作
	}
	~Impl()
	{
		// TODO: 可以在这里做一些清理工作
	}


public:
	void LoadConfig()
	{
		// 省略具体的实现
	}

	// 省略其他的方法

public:
	SOCKET              m_hSocket;
	short               m_nPort;
	char                m_szServer[64];
	long                m_nLastDataTime;
	long                m_nHeartbeatInterval;
	CRITICAL_SECTION    m_csLastDataTime;
	HANDLE              m_hSendDataThread;
	HANDLE              m_hRecvDataThread;
};



CSocketClient::CSocketClient() : m_pImpl(std::make_unique<Impl>())
{
}

CSocketClient::~CSocketClient()
{
	//delete m_pImpl;
}

void CSocketClient::test() {
	std::cout << "test method." << std::endl;
}
