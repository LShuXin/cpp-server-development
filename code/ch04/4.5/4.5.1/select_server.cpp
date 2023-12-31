/**
 * select 函数示例，服务端
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <vector>
#include <errno.h>


// 自定义代表无效 fd 的值
#define INVALID_FD -1

int main(int argc, char* argv[])
{
    // 创建一个监听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == INVALID_FD)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    // 初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);

    if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error" << std::endl;
        return -1;
    }

    // 启动监听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error" << std::endl;
        close(listenfd);
        return -1;
    }

    // 存储客户端socket的数组
    std::vector<int>   clientfds;
    int maxfd;

    while (true)
    {
        fd_set readset;
        FD_ZERO(&readset);

        // 将监听socket 加入待检测的可读事件中
        FD_SET(listenfd, &readset);
        
        maxfd = listenfd;
        // 将客户端fd加入待检测的可读事件中
        int clientfdslength = clientfds.size();
        for (int i = 0; i < clientfdslength; ++i)
        {
            if (clientfds[i] != INVALID_FD)
            {
                FD_SET(clientfds[i], &readset);

                if (maxfd < clientfds[i])
                {
                    maxfd = clientfds[i];
                }
            }
        
        }

        timeval tm;
        tm.tv_sec = 0;
        tm.tv_usec = 1000;

        // 暂且只检测可读事件，不检测可读和异常事件
        int ret = select(maxfd + 1, &readset, NULL, NULL, &tm);
        if (ret == -1)
        {
            if (errno != EINTR)
            {
                break;
            }
        }
        else if (ret == 0)
        {
            // select 函数超时，下次继续
            continue;
        }
        else
        {
            // 监听到listensocket有事件，说明来了连接请求
            if (FD_ISSET(listenfd, &readset))
            {
                // 监听socket 的可读事件，表明有新的连接到来
                struct sockaddr_in clientaddr;
                socklen_t clientaddrlen = sizeof(clientaddr);
                // 接受客户端连接
                int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
                if (clientfd == INVALID_FD)
                {
                    // 接受客户端连接出错
                    break;
                }

                // 只接受连接，不调用recv收取任何数据
                std::cout << "accept a client connection fd: " << clientfd << std::endl;
                clientfds.push_back(clientfd);
            }
            else
            {
                // 假设对端发来的数据不超过63个字符
                char recvBuf[64];
                int clientfdslength = clientfds.size();
                for (int i = 0; i < clientfdslength; ++i)
                {
                    if (clientfds[i] != INVALID_FD && FD_ISSET(clientfds[i], &readset))
                    {
                        memset(recvBuf, 0, sizeof(recvBuf));
                        // 非监听soccet， 接受数据
                        int length = recv(clientfds[i], recvBuf, 64, 0);
                        if (length <= 0)
                        {
                            std::cout << "recv data error, clientfd: " << clientfds[i] << std::endl;
                            close(clientfds[i]);
                            // 不直接删除该元素，将该位置的元素标记为INVALID_FD
                            clientfds[i] = INVALID_FD;
                            continue;
                        }
                        std::cout << "clientfd: " << clientfds[i] << "recv data: " << recvBuf << std::endl;
                    }
                }
            }
        }
    }

    // 关闭所有客户端socket
    int clientfdslength = clientfds.size();
    for (int i = 0; i < clientfdslength; ++i)
    {
        if (clientfds[i] != INVALID_FD)
        {
            close(clientfds[i]);
        }
    }

    // 关闭监听 socket
    close(listenfd);

    return 0;
}


