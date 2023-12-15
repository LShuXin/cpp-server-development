// CThread.cpp

#include "CThread.h"

// 这里开头就不用使用 static 了
#ifdef WIN32
DWORD WINAPI CThread::_ThreadEntry(LPVOID pParameter)
#else
void* CThread::_ThreadEntry(void* pParameter)
#endif
{
    CThread* pThread = (CThread*)pParameter;
    if (pThread->InitInstance())
    {
        pThread->Run();
    }

    pThread->ExitInstance();

    return NULL;
}

CThread::CThread()
{
    m_hThread = (THREAD_HANDLE)0;
    m_IDThread = 0;
}

CThread::~CThread()
{

}

bool CThread::Create()
{
    if (m_hThread != 0)
    {
        return true;
    }
    
    bool ret = true;
#ifdef WIN32
    m_hThread = CreateThread(NULL, 0, _ThreadEntry, this, 0, &m_IDThread);
    if (m_hThread == NULL)
    {
        ret = false;
    }
#else
    ret = (pthread_create(&m_hThread, NULL, &_ThreadEntry, this) == 0);
    m_IDThread = m_hThread;
#endif
    
    return ret;
}

bool CThread::InitInstance()
{
    return true;
}

void CThread::ExitInstance()
{

}

void CThread::OSSleep(int nSec)
{
#ifdef WIN32
    ::Sleep(nSec * 1000);
#else
    ::sleep(nSec);
#endif
}

void CThread::SleepMS(int nMS)
{
#ifdef WIN32
    ::Sleep(nMS);
#else
    ::usleep(nMS);
#endif
}

bool CThread::IsCurrentThread()
{
#ifdef WIN32
    return m_IDThread == ::GetCurrentThreadId();
#else
    return m_IDThread == ::pthread_self();
#endif
}

THREAD_HANDLE CThread::GetHandle()
{
    return m_hThread;
}

bool CThread::Join()
{
    THREAD_HANDLE hThread = GetHandle();
    if (hThread == (THREAD_HANDLE)0)
    {
        return true;
    }
#ifdef WIN32
    return (::WaitForSingleObject(hThread, INFINITE) != 0);
#else
    return (::pthread_join(hThread, NULL) == 0);
#endif
}

void CThread::ExitThread()
{
#ifdef WIN32
    ::ExitThread(0);
#else
#endif
}
