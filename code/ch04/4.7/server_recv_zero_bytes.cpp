/**
 * 验证 recv 函数接受0字节数据时的行为
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <vector>


int main(int argc, char* argv[])
{
  // 1. 创建一个监听 socket
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1)
  {
    std::cout << "create listen socket error." << std::endl;
    return -1;
  }

  // 2. 初始化服务器地址
  struct sockaddr_in bindaddr;
  bindaddr.sin_family = AF_INET;
  bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bindaddr.sin_port = htons(3000);
  if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
  {
    std::cout << "bind listen socket error" << std::endl;
    close(listenfd);
    return -1;
  }

  // 3. 启动监听
  if (listen(listenfd, SOMAXCONN) == -1)
  {
    std::cout << "listen error." << std::endl;
    close(listenfd);
    return -1;
  }

  int clientfd;
  struct sockaddr_in clientaddr;
  socklen_t clientaddrlen = sizeof(clientaddr);
  // 4. 接受客户端连接
  clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
  if (clientfd != -1)
  {
    while (true)
    {
      char recvbuf[32] = { 0 };
      // 5. 从客户端接收数据，客户端没有数据过来时会在recv函数处阻塞
      int ret = recv(clientfd, recvbuf, 32, 0);
      if (ret > 0)
      {
        std::cout << "recv data from client, data:" << recvbuf << std::endl;
      }
      else if (ret == 0)
      {
        // 假设recv返回值为0时收到了0字节数据（实际不会）
        std::cout << "recv 0 byte data." << std::endl;
        continue;
      }
      else
      {
        // 出错
        std::cout << "recv data error" << std::endl;
        break;
      }
    }
  }

  // 6. 关闭客户端socket
  close(clientfd);
  // 7. 关闭监听socket
  close(listenfd);
  return 0;
}
