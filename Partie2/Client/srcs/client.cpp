#include "client.hpp"

Client::Client(){}

Client::Client(std::string ip) : _ipServ(ip) {
    this->setup();
}

void Client::setup(){
    this->_servAddr.sin_family = AF_INET;
    this->_servAddr.sin_port = htons(PORT);

    if ((this->_clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Can't create a socket: " << strerror(errno) << std::endl;
        this->sShutdown();
    }

    if (connect(this->_clientSock, reinterpret_cast<struct sockaddr*>(&this->_servAddr), sizeof(this->_servAddr)) < 0){
        std::cout << "Can't connect to server: " << strerror(errno) << std::endl;
        this->sShutdown();
    }
    std::cout << "You're connected!" << std::endl;
    this->handleClient();
}


void Client::handleClient(){ //temporaire
    int answer = 0;
    while ( answer != 1 && answer != 2 ) {
        std::cout << "Write 1 for login or 2 for register:" << std::endl;
        std::cin >> answer;
        this->myFlush(); //magique !
    }
    answer == 1 ? this->login() : this->letsRegister();

}

void Client::login(){
    int protocol = 2;

    std::string username;
    std::string password;
    int ServerAnswer = 0;

    while(! ServerAnswer){
        this->sendInt(protocol);
        std::cout << "Write your username :";
        std::cin >> username;
        this->myFlush();
        password = getpass("Password (password will not be shown) :");

        sendStr(username);
        sendStr(password);
        ServerAnswer = recvInt();

        if(! ServerAnswer){
            std::cout << "Invalid username or password." << std::endl;
        } else {
            std::cout << "You are now logged in !" << std::endl;
            this->beforeGameLoop();
        }
    }
}

void Client::letsRegister(){
    int protocol = 1;

    this->sendInt(protocol);
    std::string username;
    std::string password;
    std::string password2;
    std::string email;
    int ServerAnswer = 0;
    std::regex regEmail("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\\])");
    while(! ServerAnswer){
        std::cout << "Write your new username: ";
        std::cin >> username;
        myFlush();
        std::cout << "Write your email: ";
        std::cin >> email;
        myFlush();
        password = getpass("New password (will not be shown): ");
        password2 = getpass("New password (again): ");
        if (password != password2){
            std::cout << "Password does not match!" << std::endl;
            continue;
        }
        if (std::regex_match(email.begin(), email.end(), regEmail)){
            sendStr(username);
            sendStr(password);
            sendStr(email);
            ServerAnswer = this->recvInt();
            if(! ServerAnswer){
                std::cout << "Invalid username." << std::endl;
                sendInt(protocol);
            }
        } else {
            std::cout << "Invalid email." << std::endl;
        }
    }
}

void Client::beforeGameLoop(){ //temporaire
    int answer;
    while (true){
        std::cout << "Write 1 for exit, 2 for chat, 3 for game: " << std::endl;
        std::cin >> answer;
        if (answer == 1){
            break;
        }
        else if (answer == 2){
            this->chat();
        }
        else if (answer == 3){
            this->inGameLoop();
        }
    }
}

void Client::inGameLoop(){ //temporaire
    int answer;
    std::vector<int> listMov;
    while (true){
        std::cout << "Write 1 for surrend, 2 for chat, 3 for checkmov";
        if (! listMov.empty())
                std::cout << ", 4 for mov";
        std::cout << std::endl;
        std::cin >> answer;
        if (answer == 1){
            break;
        }
        else if (answer == 2){
            ;;
        }
        else if (answer == 3){
            ;;
        }
        else if(! listMov.empty() && answer == 4){

        }
    }
}

void Client::exit(){
    int protocol = 0;
}
/*
void Client::findMatch(int modDeJeu, std::string name){
    int protocol = 3;
    ;;
}
*/
void Client::chat(){
    int protocol = 3;
    sendInt(protocol);
}

void Client::checkmov(){
    int protocol = 4;
    ;;
}

void Client::mov(){
    int protocol = 5;
    ;;
}

void Client::surend(){
    int protocol = 7;
    ;;
}

////////////////////////////////////////////////////////////////////////////////////////
void Client::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        this->sShutdown();
    }
}

int Client::recvInt(){
    uint16_t tmpAnswer;
    if (recv(this->_clientSock, &tmpAnswer, sizeof(uint16_t), MSG_WAITALL) <= 0){
        this->sShutdown();
    }
    return ntohs(tmpAnswer);
}

void Client::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->sShutdown();
    }
}

void Client::sShutdown(){
    close(this->_clientSock);
}

void Client::myFlush(){ //delete for the 3 part
    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Client::~Client(){
}
