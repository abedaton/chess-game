#include "Serveur.hpp"

Serveur::Serveur(){}

Serveur::Serveur(short unsigned int port) : _port(port) {
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




std::vector<User*> onlineUsers; 

/*
on update la bdd seulement quand on ajoute/supprimme ami ou a chaque deconnexions ?
todo rendre onlineUsers thread safe?

*/

void Serveur::mainLoop(){
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
 
    while (true){
        if ((tmpClient = accept(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), reinterpret_cast<socklen_t*>(&this->_addrlen))) >= 0){
            std::cout << "Nouvelle connexion et le socket est : " << tmpClient << std::endl;
            if (tmpClient != -1){
                if (static_cast<size_t>(tmpClient) > this->_clients.size()){
                     this->_clients.resize(static_cast<size_t>(tmpClient));       
                    std::cout << "resize" << std::endl;
                }
                this->_clients.at(static_cast<unsigned long int>(tmpClient-1)) = tmpClient;
                User* tmpUser = new User(tmpClient); // <------ new important pour polymorphisme! - Quentin
                
                /*
                j'ai juste laissé ca pour un test au cas ou je veux que chaque utilisateur soit ami avec tout le monde
                for(int i = 0; i < onlineUsers.size(); i++)
                {
                    //query bdd if(tmpUser friends with onlineUsers[i]) on les ajoute en amis
                    onlineUsers[i]->addFriendToList(tmpUser);
                    tmpUser->addFriendToList(onlineUsers[i]);
                    load bdd ici ?
                }*/
                //load les amis de la bdd ici ?
                onlineUsers.push_back(tmpUser);
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
    shutdown(this->_serv_sock, SHUT_RDWR);
    for (unsigned long int i = 0; i < this->_clients.size(); i++){
        close(this->_clients.at(i));
    }
    close(this->_serv_sock);
    std::cout << "Server is now offline." << std::endl;
    exit(EXIT_SUCCESS);
}
