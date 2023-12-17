/**
 * 验证非阻塞模式下 recv 函数的行为，client 端
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

#define SERVER_ADDRESS        "127.0.0.1"
#define SERVER_PORT           3000
#define SEND_DATA


int main(int argc, char* argv[])
{
    // 1. 创建一个sockt
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create socket error." << std::endl;
        return -1;
    }

    // 2. 连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect socket error." << std::endl;
        close(clientfd);
        return -1;
    }

    // 连接成功之后，我们再将 clientfd 设置为非阻塞模式
    // 不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL, newSocketFlag) == -1)
    {
        std::cout << "set socket to non block error." << std::endl;
        close(clientfd);
        return -1;
    }


    // 直接调用recv函数
    while (true)
    {
        char recvBuf[32] = { 0 };
        // 由于 clientfd 被设置为了非阻塞模式，所以无论是否有数据，recv 函数都不会阻塞程序
        int ret = recv(clientfd, recvBuf, 32, 0);
        if (ret > 0)
        {
            // 收到数据
            std::cout << "recv successfully." << std::endl;
        }
        else if (ret == 0)
        {
            // 对端关闭连接
            std::cout << "peer close the socket." << std::endl;
            break;
        }
        else if (ret == -1)
        {
           if (errno == EWOULDBLOCK)
           {
                std::cout << "There is no data available now." << std::endl;
           }
           if (errno == EINTR)
           {
           }
        }
        else
        {
            // 真的出错了
            break;
        }
    }

    close(clientfd);

    return 0;
}
