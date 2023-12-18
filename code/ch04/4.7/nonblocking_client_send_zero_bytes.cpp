/**
 * 验证非阻塞模式下 send 函数发送0字节数据是的行为
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
#define SEND_DATA      ""


int main(int argc, char* argv[])
{
  // 1. 创建一个socket
  int clientfd = socket(AF_INET, SOCK_STREAM, 0);
  if (clientfd == -1)
  {
    std::cout << "create listen socket error." << std::endl;
    return -1;
  }

  // 2. 连接服务器
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  serveraddr.sin_port = htons(SERVER_PORT);
  if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
  {
    std::cout << "connect socker error." << std::endl;
    close(clientfd);
    return -1;
  }

  // 连接成功以后，再将clientfd设置为非阻塞的
  // 不能在创建时就设置，否则容易影响 connect 函数的行为
  int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
  int newSocketFlag = oldSocketFlag | O_NONBLOCK;
  if (fcntl(clientfd, F_SETFL, newSocketFlag) == -1)
  {
    std::cout << "set socket nonblocking error" << std::endl;
    close(clientfd);
    return -1;
  }




  // 3. 不断向服务器发送数据，或者出错退出
  int count = 0;
  while (true)
  {
    // 发送0字节数据
    int ret = send(clientfd, SEND_DATA, 0, 0);
    if (ret == -1)
    {
      // 在非阻塞模式下，send 函数由于tcp窗口太小，发不出去数据，错误码是 EWOULDBLOCK
      if (errno == EWOULDBLOCK)
      {
        std::cout << "send data error as TCP Window size is to small." << std::endl;
        continue;
      }
      else if (errno == EINTR)
      {
        // 如果被信号中断，则继续重试
        std::cout << "sending data interrupted by signal." << std::endl;
        continue;
      }
      else
      {
          std::cout << "send data error" << std::endl;
          break;
      }
    }
    else if (ret == 0)
    {
      // 发送了0字节数据
      std::cout << "send 0 byte data." << std::endl;
    }
    else
    {  
      count++;
      std::cout << "send data successfully, count = " << count << std::endl;
    }

    // 每3秒发送一次
    sleep(3);
  }


  // 5. 关闭socket
  close(clientfd);

  return 0;
}
