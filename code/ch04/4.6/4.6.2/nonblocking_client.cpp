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
#define SERVER_PORT 3000
#define SEND_DATA "helloworld"

int main(int argc, char* argv[])
{
    // 1. 创建一个sockt
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
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

    // 连接成功后，我们再将 clientfd 设置为非阻塞模式
    // 不能在创建时就设置，这样会影响到 connect 函数的行为
    int oldSocketFlag = fcntl(clientfd, F_GETFL, 0);
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if (fcntl(clientfd, F_SETFL, newSocketFlag) == -1)
    {
        close(clientfd);
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    // 3. 不断向服务端发送数据，知道出错，出错时退出
    int count = 0;
    while (true)
    {
        int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
        if  (ret == -1)
        {
            // 非阻塞模式下，send 函数由于tcp窗口太小发不出去数据，错误码是 EWOULDBLOCK
            if (errno == EWOULDBLOCK)
            {
                std::cout << "send data error as tcp window size is to small." << std::endl;
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
            }
        }
        else if (ret == 0)
        {
            // 对端关闭了连接，我们也关闭
            std::cout << "send data error" << std::endl;
            close(clientfd);
            break;
        }
        else
        {
            count++;
            std::cout << "send data successfully, count = " << count << std::endl;
        }
    }

    // 4. 关闭 socket
    close(clientfd);

    return 0;
}

