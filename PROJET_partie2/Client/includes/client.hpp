#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <thread>
#include <iostream>
#include <regex>
#include <cstring>
#include <cstdlib>
#include "arpa/inet.h"
#include "sys/socket.h"
#include "errno.h"
#include "unistd.h"
#include "termios.h"
#include "stdio.h"

#define PORT 5555

class Client {
    public:
        Client(std::string ip);
        Client();
        ~Client();
        void setup();
        void login();
        void handleClient();
        void sShutdown();
        void letsRegister();

        void inGameLoop();
        void beforeGameLoop();

        void exit();
        void findMatch(int modDeJeu, std::string name);
        void chat();
        void checkmov();
        void mov();
        void surend();
    private:
        static void myFlush();
        void sendStr(std::string str);
        int recvInt();
        void sendInt(int num);
        std::string _ipServ;
        int _clientSock;
        struct sockaddr_in _servAddr;
};


#endif
