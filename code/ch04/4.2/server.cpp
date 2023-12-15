/**
 * TCP 服务器通信的基本流程（服务端）
 * */

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

int main(int argc, char* argv[])
{
    // 1. 创建一个监听socket
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
        std::cout << "bind listen socket error." << std::endl;
        return -1;
    }

    // 3. 启动监听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }

    while (true)
    {
        struct sockaddr_in clientaddr;
        socklen_t clientaddrlen = sizeof(clientaddr);
        // 4. 接受客户端连接
        int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if (clientfd != -1)
        {
            char recvBuf[32] = { 0 };
            // 5. 从客户端接收数据
            int ret = recv(clientfd, recvBuf, 32, 0);
            if (ret > 0)
            {
                std::cout << "recv data from client, data: " << recvBuf << std::endl;
                // 6. 将收到的数据原封不动的发送给客户端
                ret = send(clientfd, recvBuf, strlen(recvBuf), 0);
                if (ret != strlen(recvBuf))
                {
                    std::cout << "send data error." << std::endl;
                }
                else
                {
                    std::cout << "send data to client successfully, data: " << recvBuf << std::endl; 
                }
                close(clientfd);
            }
        }
    }

    // 7. 关闭监听socket
    close(listenfd);

    return 0;
}
