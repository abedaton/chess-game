#include "serveur.hpp"

Serveur::Serveur(){}

Serveur::Serveur(std::string ip, short unsigned int port) : _ip(ip), _port(port) {
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

    this->db = initSql();
    this->mainLoop();
}

void Serveur::mainLoop(){
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
    while (true){
        if ((tmpClient = accept(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), reinterpret_cast<socklen_t*>(&this->_addrlen))) >= 0){
            std::cout << "Nouvelle connexion!" << std::endl;
            if (tmpClient != -1){
                try {
                    if (this->_clients.at(static_cast<unsigned long int>(tmpClient)) == -1){
                        this->_clients.at(static_cast<unsigned long int>(tmpClient)) = tmpClient;
                    }
                } catch (std::out_of_range& e) {
                    this->_clients.push_back(tmpClient);
                }
                struct tmp* bob;
                bob = static_cast<struct tmp *>(malloc(sizeof(struct tmp)));
                bob->obj = this;
                bob->sock = tmpClient;
                pthread_t clientThread;
                pthread_create(&clientThread, NULL, Serveur::handleClientTmp, static_cast<void*>(bob));
            } else {
                std::cout << "Error.. socket == -1" << std::endl;
            }
        }
    }
}

void Serveur::matchMakingLoop(){ //temporaire
    while (true){
        ;;
    }
}

void* Serveur::handleClientTmp(void* tmp2){
    struct tmp* bob = static_cast<struct tmp*>(tmp2);
    std::cout << bob->sock << std::endl;
    static_cast<Serveur*>((*bob).obj)->handleClient((*bob).sock);
    return NULL;
}

void Serveur::handleClient(int client_sock){
    while (true){
        uint16_t tmpAnswer;
        if (recv(client_sock, &tmpAnswer, sizeof(uint16_t), MSG_WAITALL) <= 0){
            std::cout << "Client disconnected " << std::endl;
            this->kickClient(client_sock);
            break;
        } else {
            uint16_t answer = ntohs(tmpAnswer);
            if (answer == 0) {
                this->checkLogin(client_sock); // login
            } else if (answer == 1){
                this->letsRegister(client_sock); // register
            } else if (answer == 2){
                this->kickClient(client_sock); // exit
                break;
            }
        }
    }
}

void Serveur::menu(){
  ;;
}

void Serveur::checkLogin(int client_sock) {
    // Check login
    std::cout << "checking login" << std::endl;
    std::string username = recvStr(client_sock); // x2
    std::string password = recvStr(client_sock); // x2

    std::cout << "username is " << username << std::endl; // ""
    std::cout << "password is " << password << std::endl; // ""

    bool ok = isLoginOk(this->db, username, password);

    if (ok){
        std::cout << "yup" << std::endl;
        sendInt(1, client_sock);
        this->menu();
    } else {
        std::cout << "nope" << std::endl;
        sendInt(0, client_sock);
    }
}

void Serveur::letsRegister(int client_sock){
    std::string username = recvStr(client_sock);
    std::string password = recvStr(client_sock);
    std::string email = recvStr(client_sock);

    //isUsernameFree(username);
    addUser(this->db, username, password, email);
    std::cout << "register successfull" << std::endl;

    this->sendInt(1,client_sock);
    this->menu();

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

void Serveur::isAlive(int client_sock){
    char buffer[100];
    long int newData;
    std::cout << "checking if " << client_sock << " is still conencted." << std::endl;
    newData = recv(client_sock, buffer, sizeof(buffer), MSG_WAITALL);
    if (newData <= 0 ){
        std::cout << "client is disconnected" << std::endl;
    } else {
        ;;
    }
}

void Serveur::kickClient(int client_sock){
    close(client_sock);
    long unsigned int index = static_cast<long unsigned int>(client_sock - 5);
    this->_clients.at(index) = -1;
}

void Serveur::sShutdown(){
    sqlite3_close(this->db);
    shutdown(this->_serv_sock, SHUT_RDWR);
    for (unsigned long int i = 0; i < this->_clients.size(); i++){
        close(this->_clients.at(i));
    }
    close(this->_serv_sock);
    std::cout << "Server is now offline." << std::endl;
    exit(EXIT_SUCCESS);
}


void Serveur::sendInt(int num, int clientSock){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->kickClient(clientSock);
    }
}

int Serveur::recvInt(int clientSock){
    uint16_t Answer;
    if (recv(clientSock, &Answer, sizeof(uint16_t), MSG_WAITALL) <= 0){
        std::cout << "Bad recvInt, client disconnected : " << std::endl;
        this->kickClient(clientSock);
    }
    return ntohs(Answer);
}

std::string Serveur::recvStr(int client_sock){
    int len_str = recvInt(client_sock);
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(client_sock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->kickClient(client_sock);
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}
