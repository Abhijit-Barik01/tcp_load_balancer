#ifndef CLIENT_H
#define CLIENT_H

#include <string>
class Client{
    public:
        Client(const std::string& address , int port);
        void sendRequest(const std::string& request);
    private:
        std::string serverAddress;
        int serverPort;
        int sockfd;
        void connectToServer();
};





#endif



