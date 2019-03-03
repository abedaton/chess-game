#include "../includes/request.hpp"

Request::Request(AbstractClient* client): _client(client){
	setup();
	pthread_create(&this->_listenerThread, NULL, &Request::run, static_cast<void*>(this));
}

Request::~Request(){
	pthread_cancel(this->_listenerThread);
	close(this->_clientSock);
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

void Request::chat(std::string msg){
	waitForProcess();
    int protocol = 3;
    sendInt(protocol);
    sendStr(msg);
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

void Request::mov(std::string mov){
	waitForProcess();
    int protocol = 5;
	sendInt(protocol);
	sendStr(mov);
	endProcess();
}

void Request::surrend(){
	waitForProcess();
	int protocol = 6;
	sendInt(protocol);
	endProcess();
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
        protocol = recvInt(MSG_DONTWAIT);
        switch (protocol){
			case (0):
                break;
            case (20):
				startingGame();
                break;
            case (21):
                opponentMov();
                break;
			case (22):
                recvMessage();
                break;
            default:
				std::cout << "bad receive in listener: " << protocol << std::endl;
                this->error();
                break;
        }
		endProcess();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Request::startingGame(){
	int turn = recvInt();
	this->_client->startingGame(static_cast<bool>(turn-1));
}

void Request::opponentMov(){
	std::string mov = recvStr();
	this->_client->opponentMov(mov);
}

void Request::recvMessage(){
	std::string msg = recvStr();
	this->_client->printMessage(msg);
}

void Request::error(){
	this->_client->connectionError();
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
    uint16_t tmpAnswer;
    if (recv(this->_clientSock, &tmpAnswer, sizeof(uint16_t), MSG_WAITALL) <= 0){
        this->error();
    }
    return ntohs(tmpAnswer);
}

int Request::recvInt(int flag){
	uint16_t Answer;
    int res = recv(this->_clientSock, &Answer, sizeof(uint16_t), flag);
    if (res > 0){
        return ntohs(Answer);
    } else if (res < 0){
        return 0;
    } else {
        this->error();
    }
}

void Request::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->error();
    }
}

std::string Request::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        this->error();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}