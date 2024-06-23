#include "Server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include<sstream>

Server::Server(int port)
    : serverPort(port) {}

void Server::run() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(serverPort);

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << serverPort << std::endl;

    while (true) {
        int clientSockfd;
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        clientSockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSockfd < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        handleClient(clientSockfd);
        close(clientSockfd);
    }
}

void Server::handleClient(int clientSockfd) {
    char buffer[1024] = {0};
    int valread = read(clientSockfd, buffer, 1024);
    std::cout << "Client message: " << buffer << std::endl;
    std::stringstream ss;
    ss << "Hello from server " << serverPort << "";
    std::string response = ss.str();
    send(clientSockfd, response.c_str(), response.length(), 0);
}
