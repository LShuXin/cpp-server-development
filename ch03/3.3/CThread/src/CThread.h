// CThread.h

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

#ifdef WIN32
typedef HANDLE THREAD_HANDLE;
#else
typedef pthread_t THREAD_HANDLE;
#endif

class CThread
{
    public:
        CThread();
        virtual ~CThread();
        /**
         * 创建一个线程
         * @return true: 创建成功; false: 创建失败;
         * */
        virtual bool Create();
        /**
         * 获得本线程对象存储的线程句柄
         * @return 本线程对象存储的线程句柄
         * */
        THREAD_HANDLE GetHandle(); 
        void OSSleep(int nSec);
        void SleepMS(int nMS);
        bool Join();
        bool IsCurrentThread();
        void ExitThread();

    private:
        /**
         * @param pParameter 线程对象指针
         * */
#ifdef WIN32
        static DWORD WINAPI _ThreadEntry(LPVOID pParameter);
#else
        static void* _ThreadEntry(void* pParameter);
#endif
        /**
         * 虚函数，子类可以做一些实例化的初始化工作
         * @return true: 创建成功; false: 创建失败
         * */
        virtual bool InitInstance();
        /**
         * 虚函数，子类清除实例
         * */
        virtual void ExitInstance();
        /**
         * 存放线程函数的实际业务逻辑，纯虚函数，子类必须重写该函数
         * */
        virtual void Run() = 0;
    
    private:
        THREAD_HANDLE         m_hThread;
#ifdef WIN32
        DWORD                 m_IDThread;
#else
        pthread_t             m_IDThread;
#endif
};
