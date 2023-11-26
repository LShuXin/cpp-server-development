#include "CSocketClient.h"

// ������ Impl �Ķ���Ҫ���� CSocketClient ���캯������֮ǰ
// ��Ϊ CSocketClient ���캯���Ķ������õ��� Impl ��
struct CSocketClient::Impl
{
public:
	Impl()
	{
		// TODO: ����������Գ�Ա������һЩ��ʼ������
	}
	~Impl()
	{
		// TODO: ������������һЩ������
	}


public:
	void LoadConfig()
	{
		// ʡ�Ծ����ʵ��
	}

	// ʡ�������ķ���

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
