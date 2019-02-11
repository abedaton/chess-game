#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#ifndef SERVEUR_HPP
#define SERVEUR_HPP

#include "database.hpp"


class Serveur {
    public:
        Serveur();
        Serveur(std::string ip, short unsigned int port);
    private:
        void sShutdown();
        void mainLoop();
        void menu();
        void matchMakingLoop() ;//temporaire
        void setup();
        void handleClient(int client_sock);

        static void* handleClientTmp(void* tmp);

        void isAlive(int client_sock);
        void* handleCommand();
        void kickClient(int sock_client);
        void checkLogin(int client_sock);
        void letsRegister(int client_sock);


        void sendInt(int num, int clientSock);
        int recvInt(int clientSock);
        std::string recvStr(int client_sock);


        std::string _ip;
        short unsigned int _port;
        struct sockaddr_in _address;
        int _serv_sock;
        unsigned int _addrlen;

        std::vector<int> _clients;

        sqlite3 *db;
        sqlite3_stmt* stmt;
        std::string sql;
        char* zErrMsg = 0; // voir site sqlite

};
struct tmp {
        Serveur* obj ;
        int sock;
};


#endif
