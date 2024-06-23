#include "LoadBalancer.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

LoadBalancer::LoadBalancer(int port, const std::vector<std::pair<std::string, int>>& backendServers)
    : lbPort(port), backends(backendServers), currentBackend(0) {}

void LoadBalancer::run() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(lbPort);

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Load Balancer listening on port " << lbPort << std::endl;

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

int LoadBalancer::getNextBackend() {
    int backendIndex = currentBackend;
    currentBackend = (currentBackend + 1) % backends.size();
    return backendIndex;
}

void LoadBalancer::handleClient(int clientSockfd) {
    int backendIndex = getNextBackend();
    std::string backendAddress = backends[backendIndex].first;
    int backendPort = backends[backendIndex].second;

    int backendSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (backendSockfd < 0) {
        perror("Backend socket creation failed");
        return;
    }

    sockaddr_in backendAddr;
    backendAddr.sin_family = AF_INET;
    backendAddr.sin_port = htons(backendPort);

    if (inet_pton(AF_INET, backendAddress.c_str(), &backendAddr.sin_addr) <= 0) {
        perror("Invalid backend address");
        close(backendSockfd);
        return;
    }

    if (connect(backendSockfd, (struct sockaddr*)&backendAddr, sizeof(backendAddr)) < 0) {
        perror("Connection to backend failed");
        close(backendSockfd);
        return;
    }

    char buffer[1024] = {0};
    int valread = read(clientSockfd, buffer, 1024);
    send(backendSockfd, buffer, valread, 0);

    valread = read(backendSockfd, buffer, 1024);
    send(clientSockfd, buffer, valread, 0);

    close(backendSockfd);
}
