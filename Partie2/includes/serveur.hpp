#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <cstring>
#include <string>
#include <thread>

class Serveur {
    public:
        Serveur();
        Serveur(std::string ip, short unsigned int port);
    private:
        void sShutdown();
        void mainLoop();
        void setup();
        void handleClient(int client_sock);
        void isAlive(int client_sock);
        void* handleCommand();

        std::string _ip;
        short unsigned int _port;

        struct sockaddr_in _address;
        int _serv_sock;
        unsigned int _addrlen;

        std::vector<int> _clients;

};

#endif
