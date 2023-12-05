#pragma once
#ifdef WIN32
#include <WinSock2.h>
#else
#include <pthread>
#endif

#ifdef WIN32
typedef HANDLE THREAD_HANDLE;
#else
typedef pthread_t THREAD_HANDLE;
#endif

/**
 * ����һ���̶߳���
*/
class CThread
{
public:
	CThread();

	virtual ~CThread();

	/**
	 * ����һ���߳�
	 * @return true:�����ɹ��� false: ����ʧ��
	 */
	virtual bool Create();

	/**
	 * ��ñ��̶߳���洢���߳̾��
	 * @return ���̶߳���洢���߳̾��
	*/
	THREAD_HANDLE GetHandle();

	/**
	 * �߳�˯�� nSeconds ��
	 * @param nSeconds, ˯������
	*/
	void OSSleep(int nSeconds);
	void SleepMs(int mMilliseconds);
	bool join();
	bool IsCurrentThread();
	void ExitThread();

private:
#ifdef WIN32
	static DWORD WINAPI _ThreadEntry(LPVOID pParams);
#else
	static void* _ThreadEntry(void* pParams);
#endif

	/**
	 * �麯��,�������һЩʵ��������
	 * @return true: �����ɹ���false:  ����ʧ�ܣ�
	*/
	virtual bool InitInstance();

	/**
	 * �麯�����������ʵ��
	*/
	virtual void ExitInstance();

	/**
	 *  ����̺߳�����ʵ��ҵ���߼������麯�������������д�ú���
	*/
	virtual void Run() = 0;

private:
	THREAD_HANDLE    m_hThread;
	DWORD            m_IDThread;
};

