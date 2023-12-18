/**
 * Linux 上正确的异步connect 写法
 * */


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT    3000
#define SEND_DATA      "helloworld"


int main(int argc, char* argv[])
{
  // 1. 创建一个 socket
  int clientfd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientfd == -1)
  {
    std::cout << "create client socket error." << std::endl;
    return -1;
  }

  // 将 clientfd 设置为非阻塞模式
  int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
  int newSocketFlag = oldSocketFlag | O_NONBLOCK;
  if (fcntl(clientfd, F_SETFL, newSocketFlag) == -1)
  {
    std::cout << "set noblocking socket error." << std::endl;
    close(clientfd);
    return -1;
  }

  // 2. 连接服务器
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  serveraddr.sin_port = htons(SERVER_PORT);

  for (;;)
  {
    int ret = connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (ret == 0)
    {
      std::cout << "connect to server successfully." << std::endl;
      close(clientfd);
      return 0;
    }
    else if (ret == -1)
    {
      if (errno == EINPROGRESS)
      {
        // 连接正在尝试中
        break;
      }
      else if (errno == EINTR)
      {
        std::cout << "connect interruptted by signal, try again." << std::endl;
        continue;
      }
      else
      {
        std::cout << "error" << std::endl;
        close(clientfd);
        return -1;
      }
    }
  }


  fd_set writeset;
  FD_ZERO(&writeset);
  FD_SET(clientfd, &writeset);
  struct timeval tv;
  tv.tv_sec = 3;
  tv.tv_usec = 0;

  // 3. 调用 select 函数判断 socket 是否可写
  if (select(clientfd + 1, NULL, &writeset, NULL, &tv) != 1)
  {
    std::cout << "[select] connect to server error." << std::endl;
    close(clientfd);
    return -1;
  }

  int err;
  socklen_t len = static_cast<socklen_t>(sizeof err);
  // 4. 调用 getsockopt 检测此时socket 是否出错
  if (::getsockopt(clientfd, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
  {
    close(clientfd);
    return -1;
  }

  if (err == 0)
  {
    std::cout << "connect to server successfully." << std::endl;
  }
  else
  {
    std::cout << "connect to server error." << std::endl;
  }

  close(clientfd);

  return 0;
}
