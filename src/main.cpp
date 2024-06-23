#include "Client.h"
#include "Server.h"
#include "LoadBalancer.h"
#include <thread>
#include <vector>
#include <chrono>

void runServer(int port) {
    Server server(port);
    server.run();
}

void runClient(const std::string& address, int port, const std::string& message) {
    Client client(address, port);
    client.sendRequest(message);
}

void runLoadBalancer(int port, const std::vector<std::pair<std::string, int>>& backends) {
    LoadBalancer lb(port, backends);
    lb.run();
}

int main() {
    std::vector<std::thread> threads;

    // Start backend servers
    threads.emplace_back(runServer, 8081);
    threads.emplace_back(runServer, 8082);

    // Give servers some time to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Start load balancer
    std::vector<std::pair<std::string, int>> backends = {{"127.0.0.1", 8081}, {"127.0.0.1", 8082}};
    threads.emplace_back(runLoadBalancer, 8080, backends);

    // Give load balancer some time to start
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Start clients
    threads.emplace_back(runClient, "127.0.0.1", 8080, "Hello from client 1");
    threads.emplace_back(runClient, "127.0.0.1", 8080, "Hello from client 2");

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
