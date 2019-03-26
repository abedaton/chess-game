#include "../includes/request.hpp"

Request::Request(AbstractClient* client, const char* ip): _client(client){
    std::pair<Request*, const char*> params(this, ip);
	pthread_create(&this->_listenerThread, NULL, &Request::run, &params);
}

Request::~Request(){
	pthread_cancel(this->_listenerThread);
	close(this->_clientSock);
}


//////////////////////////////////////////////////////////////////////////////////////////////PRIVIET
void* Request::run(void* tmp){
    std::pair<Request*, const char*> params = *(std::pair<Request*, const char*>*)tmp;
    (params.first)->setup(params.second);
    return NULL;
}

void Request::setup(const char* ip){
    this->_servAddr.sin_addr.s_addr	= inet_addr(ip);
    this->_servAddr.sin_family = AF_INET;
    this->_servAddr.sin_port = htons(PORT);

    if ((this->_clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "A" << std::endl;
        this->error();
    }
    if (connect(this->_clientSock, reinterpret_cast<struct sockaddr*>(&this->_servAddr), sizeof(this->_servAddr)) < 0){
        std::cout << strerror(errno) << std::endl;
        std::cout << "B" << std::endl;
        this->error();
    } else {
        std::cout << "You're connected!" << std::endl;
    }
    listener();
}

void Request::listener(){
	int protocol;
    while (true){
		waitForProcess();
        protocol = recvInt(MSG_DONTWAIT);
        switch (protocol){
			case 0:
                break;
            case STARTGAME: // 25
				startingGame();
                break;
            case OPPONENTMOV: // 26
                opponentMov();
                break;
			case RECVMESSAGEINGAME: // 27
                recvMessageInGame(); // in game chat
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
	std::string ennemy_name = recvStr();

	this->_client->startingGame(static_cast<bool>(turn-1), ennemy_name);
}

void Request::opponentMov(){
	std::string mov = recvStr();
	this->_client->opponentMov(mov);
}

void Request::recvMessageInGame(){
	std::string msg = recvStr();
	this->_client->recvMessage("opponent", msg);
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
        return -1;
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

void Request::sendMessage(std::string name, std::string msg){
    std::cout << "A" << std::endl;
    waitForProcess();
    std::cout << "B" << std::endl;
    int protocol = 7;
    sendInt(protocol);
    std::cout << "C" << std::endl;
    sendStr(name);
    std::cout << "D" << std::endl;
    sendStr(msg);
    std::cout << "E" << std::endl;
    endProcess();
}

void Request::recvMessage(){
    std::string name = recvStr();
    std::string msg = recvStr();
    //TO DO (send to client and interface)
}

void Request::addFriend(std::string name){
    waitForProcess();
    int protocol = 8;
    sendInt(protocol);
    sendStr(name);
    endProcess();
}

void Request::removeFriend(std::string name){
    waitForProcess();
    int protocol = 9;
    sendInt(protocol);
    sendStr(name);
    endProcess();
}

void Request::acceptFriend(std::string name, bool accept){
    waitForProcess();
    int protocol = 10;
    sendInt(protocol);
    sendStr(name);
    sendInt(static_cast<int>(accept)+1);
    endProcess();
}

void Request::getFriendList(){
    waitForProcess();
    int protocol = 11;
    sendInt(protocol);
    endProcess();
}

void Request::getFriendRequests(){
    waitForProcess();
    int protocol = 12;
    sendInt(protocol);
    endProcess();
}

void Request::getOnlineFriendList(){
    waitForProcess();
    int protocol = 13;
    sendInt(protocol);
    endProcess();
}

void Request::getMyInfo(){
    waitForProcess();
    int protocol = 14;
    sendInt(protocol);
    endProcess();
}

void Request::getUserInfo(std::string username){
    waitForProcess();
    int protocol = 15;
    sendInt(protocol);
    sendStr(username);
    endProcess();
}
