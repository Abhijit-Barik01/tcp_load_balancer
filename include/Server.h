#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int port);
    void run();

private:
    int serverPort;
    int sockfd;
    void handleClient(int clientSockfd);
};

#endif // SERVER_H
