#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <list>
#include <condition_variable>
#include <memory>

class Task
{
public:
  virtual void doIt()
  {
    std::cout << "do a task" << std::endl;
  }
  
  virtual ~Task()
  {
    std::cout << "task destructed"  << std::endl;
  }
};

class TaskPool final
{
    public:
        TaskPool();
        ~TaskPool();
        // 拷贝构造函数
        TaskPool(const TaskPool &rhs) = delete;
        // 赋值构造函数
        TaskPool& operator=(const TaskPool &rhs) = delete;
    public:
        void Init(int threadNum = 5);
        void addTask(Task* pTask);
        void removeAllTasks();
        void stop();
    private:
        void threadFunc();
    private:
        bool                                        m_bRunning;
        std::mutex                                  m_mutexTasks;
        std::condition_variable                     m_cv;
        std::list<std::shared_ptr<Task>>            m_listTasks;
        std::vector<std::shared_ptr<std::thread>>   m_threads;
};