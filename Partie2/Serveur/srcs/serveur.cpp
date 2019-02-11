#include "serveur.hpp"

Serveur::Serveur(){}

Serveur::Serveur(std::string ip, short unsigned int port) : _ip(ip), _port(port) {
    this->db = new Database();
    this->match = new MatchMaking();
    this->setup();
}

void Serveur::setup(){
    this->_address.sin_family = AF_INET;
    this->_address.sin_port = htons(this->_port);
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_addrlen = sizeof(this->_address);

    if ((this->_serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    } else {
        std::cout << "Socket created !" << std::endl;
    }

    if (bind(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), this->_addrlen) < 0){
        std::cout << "Error on bind: " << strerror(errno) << std::endl;
        this->sShutdown();
    } else {
        std::cout << "Bind successfull !" << std::endl;
    }

    if (listen(this->_serv_sock, 3) < 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    }

    this->mainLoop();
}

void Serveur::mainLoop(){
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
    while (true){
        if ((tmpClient = accept(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), reinterpret_cast<socklen_t*>(&this->_addrlen))) >= 0){
            std::cout << "Nouvelle connexion !" << std::endl;
            if (tmpClient != -1){
                int* socket;
                try {
                    if (*this->_clients.at(static_cast<unsigned long int>(tmpClient)) == -1){
                        this->_clients.at(static_cast<unsigned long int>(tmpClient)) = &tmpClient;
                        socket = _clients.at(static_cast<unsigned long int>(tmpClient));
                    }
                } catch (std::out_of_range& e) {
                    this->_clients.push_back(&tmpClient);
                    socket = _clients.at(static_cast<unsigned long int>(_clients.size()-1));
                }
                User us = User(socket, this->db, this->match);
            } else {
                std::cout << "Error.. socket == -1" << std::endl;
            }
        }
    }
}


void* Serveur::handleCommand(){
    std::string command;
    while (true) {
        getline(std::cin, command);
        if (command == "shutdown"){
            this->sShutdown();
            break;
        }
    }
    return NULL;
}


void Serveur::sShutdown(){
    sqlite3_close(this->db->getdb());
    shutdown(this->_serv_sock, SHUT_RDWR);
    for (unsigned long int i = 0; i < this->_clients.size(); i++){
        close(*this->_clients.at(i));
    }
    close(this->_serv_sock);
    std::cout << "Server is now offline." << std::endl;
    exit(EXIT_SUCCESS);
}