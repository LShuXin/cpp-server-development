#include "TaskPool.h"
#include <chrono>

int main()
{
  TaskPool taskPool;
  taskPool.Init();

  Task* pTask = NULL;
  for (int i = 0; i < 1000; ++i)
  {
    pTask = new Task();
    taskPool.addTask(pTask);
  }

  std::this_thread::sleep_for(std::chrono::seconds(30));
  taskPool.stop();

  return 0;
}


