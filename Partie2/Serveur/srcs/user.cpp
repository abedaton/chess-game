#include "user.hpp"

User::User(int* client_sock, Database* db, MatchMaking* match) : _clientSock(client_sock), _db(db), _match(match), isLog(false), inGame(false) {
    pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

void* User::run(void* tmp){
    static_cast<User*>(tmp)->handleClient();
    return NULL;
}

void User::handleClient(){
	while (true){
        int protocol = this->recvInt();
        if (protocol == 0) { // exit
            this->exit();
             break;
        } else if (protocol == 1){ // register
            this->letsRegister();
        } else if (protocol == 2){ // login
            this->checkLogin();
        } else if (protocol == 3){ // chat
            ;;
        } else if (protocol == 4){ // matchMaking
            this->waitForMatch();
        } else if (protocol == 5){ // getMov
            this->getMov();
        } else if (protocol == 6){ // Mov
            this->mov();
        }
        //...
    }
}

void User::exit() {
    close(*this->_clientSock);
    *this->_clientSock = -1;
    std::cout << "exiting.." << std::endl;
    pthread_exit(0);
}

void User::letsRegister() {
    std::string username = recvStr();
    std::string password = recvStr();
    std::string email = recvStr();

    if (this->_db->isUsernameFree(username)){
        this->_db->addUser(username, password, email);
        std::cout << "register successfull" << std::endl;
        this->name = username;
        this->isLog = true;
        this->sendInt(1);
    }
    else{
         this->sendInt(0);
    }
}

void User::checkLogin() {
    std::cout << "checking login" << std::endl;
    std::string username = recvStr();
    std::string password = recvStr();

    if (this->_db->isLoginOk(username,password)){
        std::cout << "yup" << std::endl;
        this->name = username;
        this->isLog = true;
        this->sendInt(1);
    } else {
        std::cout << "nope" << std::endl;
        this->sendInt(0);
    }
}

void User::chat(){
    ;;
}

void User::waitForMatch(){
    int gameMod = recvInt();
    //int elo = this->db->getElo(this->name));
    this->_match->waitForMatch(this,gameMod);
}

void User::getMov(){
    std::string str = recvStr();
    std::string answear = this->_game->getMov(str);
    sendStr(answear);
}

void User::mov(){
    std::string str = recvStr();
    this->_game->mov(str);
}

void User::startGame(AbstractGame* game){
    this->_game = game;
    this->inGame = true;
}

void User::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(*this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

int User::recvInt(){
    uint16_t Answer;
    if (recv(*this->_clientSock, &Answer, sizeof(uint16_t), MSG_WAITALL) <= 0){ 
        std::cout << "Bad recvInt, client disconnected : " << std::endl; 
        this->exit();
    }
    return ntohs(Answer);
}

void User::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(*this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

std::string User::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(*this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->exit();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}
