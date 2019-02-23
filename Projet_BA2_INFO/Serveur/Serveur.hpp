#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include <iostream>
#include <string>

#include "User/User.cpp"

//#include "includes/database.hpp"
//#include "includes/matchMaking.hpp"

class Serveur {
    public:
        Serveur();
        Serveur(std::string ip, short unsigned int port);
    private:
        void sShutdown();
        void mainLoop();
        void setup();
        void* handleCommand();
 

        std::string _ip;
        short unsigned int _port;
        struct sockaddr_in _address;
        int _serv_sock;
        unsigned int _addrlen;

        std::vector<int> _clients;
};

#endif
