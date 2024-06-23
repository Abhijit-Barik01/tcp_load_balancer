#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <vector>
#include <string>
#include <netinet/in.h>

class LoadBalancer {
public:
    LoadBalancer(int port, const std::vector<std::pair<std::string, int>>& backendServers);
    void run();

private:
    int lbPort;
    int sockfd;
    std::vector<std::pair<std::string, int>> backends;
    int currentBackend;
    int getNextBackend();
    void handleClient(int clientSockfd);
};

#endif // LOAD_BALANCER_H
