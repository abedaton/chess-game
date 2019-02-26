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


/*
note: je suppose maintenant que tout le monde est ami avec tout le monde
apres que la bdd pour ami est implémentée je changerai ca

todo gerer les deconnexions etc
*/

void Serveur::mainLoop(){
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
    std::vector<User*> onlineUsers; //a changer c'est pas clean je trouve?
    const char *names[4] = {"george", "max", "andre"};          //juste pour un test
    int cnter = 0;  //meme chose qu'en haut

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
                tmpUser->setName(names[cnter]);
                for(int i = 0; i < onlineUsers.size(); i++)
                {
                    onlineUsers[i]->addFriendToList(tmpUser);
                    tmpUser->addFriendToList(onlineUsers[i]);
                }

                onlineUsers.push_back(tmpUser);
                cnter++;


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
