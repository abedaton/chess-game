#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "arpa/inet.h"
#include "sys/socket.h"
#include "stdio.h"

#define PORT 5555

class Client {
    public:
        Client(std::string ip);
        Client();
        ~Client();
    private:
        void setup(std::string ip);
        void handleClient();
		void sShutdown();

        void sendStr(std::string str);
        int recvInt();
        void sendInt(int num);
		std::string recvStr();
        int _clientSock;
        struct sockaddr_in _servAddr;
};


#endif
