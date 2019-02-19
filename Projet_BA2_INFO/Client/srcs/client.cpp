#include "client.hpp"

Client::Client(){}

Client::Client(std::string ip) {
    this->setup(ip);
}

void Client::setup(std::string ip){
    this->_servAddr.sin_family = AF_INET;
    this->_servAddr.sin_port = htons(PORT);

    if ((this->_clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Can't create a socket" << std::endl;
        this->sShutdown();
    }
    else if (connect(this->_clientSock, reinterpret_cast<struct sockaddr*>(&this->_servAddr), sizeof(this->_servAddr)) < 0){
        std::cout << "Can't connect to server" << std::endl;
        this->sShutdown();
    } else {
        std::cout << "You're connected!" << std::endl;
        this->handleClient();
    }
}


void Client::handleClient(){
    int answer;
	std::string str;
    while ( true ) {
		answer = recvInt();
		if (answer == 1){
			str = recvStr();
			std::cout << str << std::endl;
		}
		else{
			std::cin >> str;
			sendStr(str);
		}
    }
}

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

std::string Client::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->sShutdown();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}

void Client::sShutdown(){
    close(this->_clientSock);
    
}

Client::~Client(){
}