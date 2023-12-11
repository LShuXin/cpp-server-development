#include <stdio.h>
#include <thread>
#include <memory>

class Thread
{
public:
	Thread(){}
	~Thread(){}
	void stop()
	{
            m_stopped = true;
            if (m_spThread)
	    {
                if (m_spThread.joinable())
		{
                    m_spThread.join();
		}
	    }
	}
	void start()
	{
            m_stopped = false;
	    m_spThread.reset(new std::thread(&Thread::threadFunc, this, 100, 200));
	}
	void threadFunc(int a, int b)
	{
            while (!m_stopped)
	    {
		    printf("hahahaha, %d %d", a, b);
		    sleep(1);
	    }
	}
private:
	bool                              m_stopped;
	std::shared_ptr<std::thread>      m_spThread;

}


int main()
{
    Thread thread;
    thread.start();

    while(true)
    {
    }

    return 0;
}


