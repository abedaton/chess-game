#include "request.hpp"

Request::Request(){
	setup();
	pthread_create(&this->_listenerThread, NULL, &Request::run, static_cast<void*>(this));
}

Request::~Request(){
	pthread_cancel(this->_listenerThread);
	close(this->_clientSock);
}

void Request::exit(){ ;//utile?
	waitForProcess();
    int protocol = 0;
	sendInt(protocol);
	endProcess();
}

int Request::letsRegister(std::string username,std::string password, std::string email){
    std::cout << "sending" << std::endl;
	waitForProcess();
    int protocol = 1;
    sendInt(protocol);
    sendStr(username);
    sendStr(password);
    sendStr(email);
	int res = recvInt();
	endProcess();
    return res;
}

int Request::login(std::string username,std::string password){
	waitForProcess();
    int protocol = 2;
    sendInt(protocol);
    sendStr(username);
    sendStr(password);
	int res = recvInt();
	endProcess();
    return res;
}

void Request::chat(){
	waitForProcess();
    int protocol = 3;
    sendInt(protocol);
	endProcess();
}

void Request::findMatch(int modDeJeu){
	waitForProcess();
    int protocol = 4;
	sendInt(protocol);
    sendInt(modDeJeu);
	endProcess();
}

//std::vector<int>  Request::getMov(int coord){ //OLD
//	waitForProcess();
//    int protocol = 5;
//	sendInt(protocol);
//	sendInt(coord);
//	std::vector<int>::size_type nbMov = static_cast<std::vector<int>::size_type>(recvInt());
//	std::vector<int> listMov(nbMov);
//	for (std::vector<int>::size_type c=0;c<nbMov;c++){
//		listMov[c] = recvInt();
//	}
//	endProcess();
//	return listMov;
//}

void Request::mov(int coord1, int coord2){
	waitForProcess();
    int protocol = 6;
	sendInt(protocol);
	sendInt(coord1);
	sendInt(coord2);
	endProcess();
}

void Request::surrend(){
	waitForProcess();
	//int protocol = 7;
	//TO DO
	endProcess();
}




//Fonctions par rapport aux liste d'amis ici:

bool Request::listOnlineFriends()
{
    bool res;
    sendInt(LISTONLINEFRIENDS);
    int friendsOnline = recvInt();
    if(friendsOnline >= 0)
    {
        std::cout << "Vous avez: " << friendsOnline <<  "ami(s) en ligne" << std::endl; 
        for(int i = 0; i < friendsOnline; i++)
            std::cout << recvStr() << "is online " << std::endl;
    }
    else
        res = false;
    return res;
}



//////////////////////////////////////////////////////////////////////////////////////////////PRIVIET
void Request::setup(){
    this->_servAddr.sin_addr.s_addr	= inet_addr(IP);
    this->_servAddr.sin_family = AF_INET;
    this->_servAddr.sin_port = htons(PORT);

    if ((this->_clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        this->error();
    }
    if (connect(this->_clientSock, reinterpret_cast<struct sockaddr*>(&this->_servAddr), sizeof(this->_servAddr)) < 0){
        this->error();
    } else {
        std::cout << "You're connected!" << std::endl;
    }
}

void* Request::run(void* tmp){
    static_cast<Request*>(tmp)->listener();
    return NULL;
}

void Request::listener(){
	int protocol;
	while (true){
		waitForProcess();
        protocol = recvInt(MSG_PEEK);
        switch (protocol){
			case (0):
                break;
            case (20):
				//
                break;
            case (21):
                //
                break;
            default:
				std::cout << "bad recive in listener: " << protocol << std::endl;
                break;
        }
		endProcess();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Request::error(){
	//this->client->connectionError();
}

inline void Request::waitForProcess(){
	this->_mutex.lock();
}


inline void Request::endProcess(){
	this->_mutex.unlock();
}

 void Request::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        this->error();
    }
}

int Request::recvInt(){
	return recvInt(MSG_WAITALL);
}

int Request::recvInt(int flag){
	uint16_t tmpAnswer;
    if (recv(this->_clientSock, &tmpAnswer, sizeof(uint16_t), flag) <= 0){
        this->error();
    }
    return ntohs(tmpAnswer);
}

void Request::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->error();
    }
}

std::string Request::recvStr()
{
    std::string res;
    int size = this->recvInt();
    if(size > 0)
    {
        char *str = new char[size+1];
        std::memset(str, 0, size+1);

        if(recv(this->_clientSock, str, size, MSG_WAITALL))
            this->error();
        res = str;
        delete[] str;
    }
    else{
        res = "error";
    }
    return res;
}










