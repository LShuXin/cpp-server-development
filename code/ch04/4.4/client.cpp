#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

#define SERVER_ADDRESS "127.0.0.1"
#define SERVER_PORT 3000
#define SEND_DATA "helloworld"

int main(int argc, char* argv[])
{
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1)
    {
        std::cout << "create client socket error." << std::endl;
        return -1;
    }

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    serveraddr.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        std::cout << "connect to server error." << std::endl;
        return -1;
    }

    int ret = send(clientfd, SEND_DATA, strlen(SEND_DATA), 0);
    if (ret != strlen(SEND_DATA))
    {
        std::cout << "send data error" << std::endl;
        return -1;
    }

    std::cout << "send data successfully, data: " << SEND_DATA << std::endl;

    char recvBuf[32] = {0};
    ret = recv(clientfd, recvBuf, 32, 0);
    if (ret > 0)
    {
        std::cout << "recv data successfully, data: " << recvBuf << std::endl;
    }
    else
    {
        std::cout << "recv data error." << std::endl;
    }



    while (true)
    {
        sleep(3);
    }


    return 0;
}

