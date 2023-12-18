/**
 * 演示 poll 函数的用法
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <errno.h>


// 无效fd 标记
#define INVALID_FD -1

int main(int argc, char* argv[])
{
  // 1. 创建一个监听socket
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd == -1)
  {
    std::cout << "create listen socker error." << std::endl;
    return -1;
  }

  // 将监听 socket 设置为非阻塞的
  int oldSocketFlag = fcntl(listenfd, F_GETFL, 0);
  int newSocketFlag = oldSocketFlag | O_NONBLOCK;
  if (fcntl(listenfd, F_SETFL, newSocketFlag) == -1)
  {
    std::cout << "set nonblocking socket error." << std::endl;
    close(listenfd);
    return -1;
  }

  // 复用地址和端口号
  int on = 1;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char*)&on, sizeof(on));

  // 初始化服务器的地址
  struct sockaddr_in bindaddr;
  bindaddr.sin_family = AF_INET;
  bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bindaddr.sin_port = htons(3000);
  if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
  {
    std::cout << "bind listen socket error." << std::endl;
    close(listenfd);
    return -1;
  }

  // 启动监听
  if (listen(listenfd, SOMAXCONN) == -1)
  {
    std::cout << "listen error." << std::endl;
    close(listenfd);
    return -1;
  }

  std::vector<pollfd> fds;
  pollfd listen_fd_info;
  listen_fd_info.fd = listenfd;
  listen_fd_info.events = POLLIN;
  listen_fd_info.revents = 0;
  fds.push_back(listen_fd_info);

  // 是否存在无效的fd标签
  bool exist_invalid_fd;
  int n;
  while (true)
  {
    exist_invalid_fd = false;
    n = poll(&fds[0], fds.size(), 1000);
    if (n < 0)
    {
      // 被信号中断
      if (errno == EINTR)
      {
        continue;
      }

      // 出错退出
      break;
    }
    else if (n == 0)
    {
      // 超时，继续
      continue;
    }

    for (n = 0; n < fds.size(); ++n)
    {
      // 事件可读
      if (fds[n].revents & POLLIN)
      {
        if (fds[n].fd == listenfd)
        {
          // 监听socket 接受新连接
          struct sockaddr_in clientaddr;
          socklen_t clientaddrlen = sizeof(clientaddr);
          // 接受客户端连接并将产生的clientfd加入fds集合中
          int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
          if (clientfd != -1)
          {
            // 将客户端socket设置为非阻塞的
            int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
            int newSocketFlag = oldSocketFlag | O_NONBLOCK;
            if (fcntl(clientfd, F_SETFL, newSocketFlag) == -1)
            {
   
            }
            else
            {
              struct pollfd client_fd_info;
              client_fd_info.fd = clientfd;
              client_fd_info.events = POLLIN;
              client_fd_info.revents = 0;
              fds.push_back(client_fd_info);
              std::cout << "new client accept, clientfd: " << clientfd << std::endl;
            }
          }
        }
        else
        {
          // 普通 clientfd，收取数据
          char buf[64] = { 0 };
          int m = recv(fds[n].fd, buf, 64, 0);
          if (m <= 0)
          {
            if (errno != EINTR && errno != EWOULDBLOCK)
            {
              // 出错了或者对端关闭了连接，关闭对应的clientfd，并设置无效标志位
              for (std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); ++iter)
              {
                if (iter->fd == fds[n].fd)
                {
                  std::cout << "client disconnect, clientfd: " << fds[n].fd << std::endl;
                  close(fds[n].fd);
                  iter->fd = INVALID_FD;
                  exist_invalid_fd = true;
                  break;
                }
              }
            }
          }
          else
          {
            std::cout << "recv from client: " << buf << ", clientfd: " << fds[n].fd << std::endl;
          }
        }
      }
      else if (fds[n].revents & POLLERR)
      {
        // TODO: 暂且不处理
      }
    }
    if (exist_invalid_fd)
    {
      // 统一清理无效的fd
      for (std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end();)
      {
        if (iter->fd == INVALID_FD)
        {
          iter = fds.erase(iter);
        }
        else
        {
          ++iter;
        }
      }
    }
  }

  // 关闭所有socket
  for (std::vector<pollfd>::iterator iter = fds.begin(); iter != fds.end(); ++iter)
  {
    close(iter->fd);
  }

  return 0;
}
