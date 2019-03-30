#pragma once
#ifndef SERVER_CPP
#define SERVER_CPP
#include "../includes/Serveur.hpp"

/*
 * Constructeur
 */
Serveur::Serveur(short unsigned int port) : _port(port), _ready(false) {
    this->_ready = false;
    this->setup();
}

/*
 * Initialisation du serveur
 */
void Serveur::setup(){
    this->_address.sin_family = AF_INET;
    this->_address.sin_port = htons(this->_port);
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_addrlen = sizeof(this->_address);

    if ((this->_serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    }

    if (bind(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), this->_addrlen) < 0){
        std::cout << "Error on bind: " << strerror(errno) << std::endl;
        this->sShutdown();
    } 

    if (listen(this->_serv_sock, 3) < 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    }
    this->mainLoop();
}

/*
 * Crée des sockets et attend les clients et crée leur objet
 */
void Serveur::mainLoop(){
    this->_db = new Database();
    this->_db->resetStuff();
	this->_match = new MatchMaking();
    this->_ready = true;
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
    while (true){
        if ((tmpClient = accept(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), reinterpret_cast<socklen_t*>(&this->_addrlen))) >= 0){
            std::cout << "Nouvelle connexion et le socket est : " << tmpClient << std::endl;
            if (tmpClient != -1){
                if (static_cast<size_t>(tmpClient) > this->_clients.size()){
                    this->_clients.resize(static_cast<size_t>(tmpClient));
                    this->_clients[tmpClient] = std::make_pair(-1, nullptr);
                }
                this->_clients.at(static_cast<unsigned long int>(tmpClient-1)).first = tmpClient;
                User* tmpUser = new User(tmpClient, this->_db, this->_match); // <------ new important pour polymorphisme! - Quentin !!!
                this->_clients.at(static_cast<unsigned long int>(tmpClient-1)).second = tmpUser;
            }
        }
    }
}


/*
 * Permet de shutdown
 */
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


/*
 * Permet de couper le serveur
 */
void Serveur::sShutdown(){
    shutdown(this->_serv_sock, SHUT_RDWR);
    for (unsigned long int i = 0; i < this->_clients.size(); i++){
        try{
            close(this->_clients.at(i).first);
            delete this->_clients.at(i).second;
        }catch (std::exception& e){
            ;;
        }
    }
    close(this->_serv_sock);
    if (this->_ready){
        delete this->_db;
        delete this->_match;
    }
    std::cout << "Server is now offline." << std::endl;
    exit(EXIT_SUCCESS);
}

#endif