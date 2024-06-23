#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

Client::Client(const std::string& address, int port)
    : serverAddress(address), serverPort(port) {
    connectToServer();
}

void Client::connectToServer() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverAddress.c_str(), &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void Client::sendRequest(const std::string& request) {
    send(sockfd, request.c_str(), request.length(), 0);
    char buffer[1024] = {0};
    int valread = read(sockfd, buffer, 1024);
    std::cout << "Server response: " << buffer << std::endl;
    close(sockfd);
}
