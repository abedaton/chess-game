#pragma once
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "../srcs/User.cpp"

#include <iostream>
#include <string>

class Serveur {
    public:
        Serveur();
        Serveur(short unsigned int port);
    private:
        void sShutdown();
        void mainLoop();
        void setup();
        void* handleCommand();
 

        short unsigned int _port;
        struct sockaddr_in _address;
        int _serv_sock;
        unsigned int _addrlen;

        std::vector<int> _clients;
};

#endif
