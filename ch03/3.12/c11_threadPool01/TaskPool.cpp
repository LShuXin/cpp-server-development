#include "TaskPool.h"

TaskPool::TaskPool(): m_bRunning(false)
{

}

TaskPool::~TaskPool()
{
   removeAllTasks();   
}


void TaskPool::Init(int threadNum /** =5 */)
{
  m_bRunning = true;
  if (threadNum <= 0)
  {
    threadNum = 5;
  }

  for (int i = 0; i < threadNum; ++i)
  {
      std::shared_ptr<std::thread> spThread;
      spThread.reset(new std::thread(std::bind(&TaskPool::threadFunc, this)));
      m_threads.push_back(spThread);
  }
}

void TaskPool::threadFunc()
{
  std::shared_ptr<Task> spTask;

  while (true)
  {
    {
      std::unique_lock<std::mutex> guard(m_mutexTasks);
      while (m_listTasks.empty())
      {
         if (!m_bRunning)
         {
           break;
         }

         m_cv.wait(guard);
      }

      if (!m_bRunning)
      {
        break;
      }
      spTask = m_listTasks.front();
      m_listTasks.pop_front();
    }
     
    if (spTask == NULL)
    {
      continue;
    }

    spTask->doIt();
    spTask.reset();
  }

  std::cout << "thread exit, threadID:" << std::this_thread::get_id() << std::endl;
}

void TaskPool::addTask(Task *pTask)
{
  std::shared_ptr<Task> spTask;
  spTask.reset(pTask);

  {
    std::unique_lock<std::mutex> guard(m_mutexTasks);
    m_listTasks.push_back(spTask);
  }

  m_cv.notify_one();
}

void TaskPool::stop()
{
  m_bRunning = false;
  m_cv.notify_all();

  for (auto& iter: m_threads)
  {
    if (iter->joinable())
    {
      iter->join();
    }
  }
}

void TaskPool::removeAllTasks()
{
  std::unique_lock<std::mutex> guard(m_mutexTasks);
  for (auto& iter: m_listTasks)
  {
    iter.reset();
  }

  m_listTasks.clear();
}






