#pragma once
#ifndef REQUEST_CPP
#define REQUEST_CPP

#include "../includes/request.hpp"


/*
 * Constructeur de Request,
 * @params client et son ip
 * cree et lance un thread pour exécuter la request
 */
Request::Request(AbstractClient* client, const char* ip): _client(client){
    struct tmp{
        Request* obj;
        const char* ip;
    };

    struct tmp* params = static_cast<struct tmp*>(malloc(sizeof(struct tmp)));

    params->obj = this;
    params->ip = ip;
	pthread_create(&this->_listenerThread, NULL, &Request::run, static_cast<void*>(params));
}

/*
 * Destructeur de request
 */
Request::~Request(){
	close(this->_clientSock);
}


//////////////////////////////////////////////////////////////////////////////////////////////PRIVIET
/*
 * Lance la requête dans le thread du constructeur
 */
void* Request::run(void* args){
    struct tmp{
        Request* obj;
        const char* ip;
    };
    
    struct tmp* params = static_cast<struct tmp*>(args);
    (params->obj)->setup(params->ip);
    return NULL;
}

/*
 * Initialisation
 */
void Request::setup(const char* ip){
    this->_servAddr.sin_addr.s_addr	= inet_addr(ip);
    this->_servAddr.sin_family = AF_INET;
    this->_servAddr.sin_port = htons(PORT);

    if ((this->_clientSock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        //this->error();
    }
    if (connect(this->_clientSock, reinterpret_cast<struct sockaddr*>(&this->_servAddr), sizeof(this->_servAddr)) < 0){
        std::cout << strerror(errno) << std::endl;
        //this->error();
    }
    listener();
}

/*
 * Attend de recevoir un protocol pour exécuter la bonne méthode
 */
void Request::listener(){
	int protocol;
    while (true){
		waitForProcess();
        protocol = recvInt(MSG_DONTWAIT);
        switch (protocol){
			case 0:
                endProcess();
                break;
            case STARTGAME: // 25
				this->startingGame();
                break;
            case OPPONENTMOV: // 26
                this->opponentMov();
                break;
			case RECVMESSAGEINGAME: // 27
                this->recvMessageInGame(); // in game chat
                break;
            case RECVMESSAGE: // 28
                this->recvMessage(); // chat
                break;
            case SEEREQUESTS: // 29
                this->recvFriendRequestsList(); // voir les amis
                break;
            case RECVFRIENDLIST: //30
                this->recvFriendList();
                break;
            case RECVINFO: //31
                this->recvInfo();
                break;
            case FEEDBACK: //33
                this->feedback();
                break;
            case OPPONENTSURREND: //34
                endProcess();
                this->_client->opponentSurrend();
                break;
            default:
				std::cout << "bad receive in listener: " << protocol << std::endl;
		        endProcess();
                this->error();
                break;
        }
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

/*
 * Lance la partie
 */
void Request::startingGame(){
	int turn = recvInt();
	std::string ennemy_name = recvStr();
    endProcess();
	this->_client->startingGame(static_cast<bool>(turn-1), ennemy_name);
}

/*
 * Recoit le move d'un string
 */
void Request::opponentMov(){
	std::string mov = recvStr();
    endProcess();
	this->_client->opponentMov(mov);
}

/*
 * Recoit un messsage du chat
 */ 
void Request::recvMessageInGame(){
	std::string msg = recvStr();
    endProcess();
	this->_client->recvMessage("opponent", msg);
}

/*
 * Recoit un vecteur 
 */
std::vector<std::string> Request::recvVector(){
    std::vector<std::string> vec;
    long size = 0;
    recv(this->_clientSock, &size, sizeof(size), MSG_WAITALL);
    size = ntohl(size);
    for (int i = 0; i < size; ++i) {
        std::string stringRead;
        long length = 0;
        recv(this->_clientSock, &length, sizeof(length), MSG_WAITALL);
        length = ntohl(length);
        while (0 < length){
            char buffer[1024];
            int cread;
            cread = recv(this->_clientSock, buffer, std::min<long>(sizeof(buffer), length), MSG_WAITALL);
            stringRead.append(buffer, cread);
            length -= cread;
        }
        vec.push_back(stringRead);
    }
    return vec;
}

/*
 * recoit la liste des demandes d'ami
 */
void Request::recvFriendRequestsList(){
    std::vector<std::string> vecRequests = this->recvVector();
    endProcess();
    this->_client->recvFriendRequestsList(vecRequests);
}

/*
 * Recoit la liste d'ami
 */
void Request::recvFriendList(){
    int len = recvInt()-1;
    std::vector<std::pair<std::string, bool> > frendList(len); 
    for (int i=0; i<len; i++){
        frendList[i].first = recvStr();
        frendList[i].second = static_cast<bool>( recvInt()-1 );
    }
    endProcess();
    this->_client->recvFriendList(frendList);
}

void Request::recvInfo(){
    std::string username = recvStr();
    int nbrgames = recvInt();
    int win = recvInt();
    int elo = recvInt();
    endProcess();
    this->_client->recvInfo(username, nbrgames, win, elo);
}

/*
 * Gère en cas d'erreur
 */
void Request::error(){
	this->_client->connectionError();
}

/*
 * lock le mutex en attendant que tout soit delock
 */
inline void Request::waitForProcess(){
	this->_mutex.lock();
}


/*
 * delock le mutex
 */
inline void Request::endProcess(){
	this->_mutex.unlock();
}

/*
 * Envoie un entier
 */
 void Request::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        this->error();
    }
}

/*
 * Recoit un entier
 */
int Request::recvInt(){
    uint16_t tmpAnswer;
    if (recv(this->_clientSock, &tmpAnswer, sizeof(uint16_t), MSG_WAITALL) <= 0){
        this->error();
    }
    return ntohs(tmpAnswer);
}

/*
 * recoit un entier
 * le flag est pour éviter le wait for all, vu la surcharge
 */
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

/*
 * envoie un std::string
 */
void Request::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->error();
    }
}

/*
 * Recoit un string
 */
std::string Request::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        this->error();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}


/*
 * Permet de créer un compte
 */
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
/*
 * Requête de login
 */ 
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

/*
 * Requête pour le chat
 */
void Request::chat(std::string msg){
	waitForProcess();
    int protocol = 3;
    sendInt(protocol);
    sendStr(msg);
	endProcess();
}

/*
 * Permet de trouver un match en fonction du mode de jeu
 */
void Request::findMatch(int modDeJeu){
	waitForProcess();
    int protocol = 4;
	sendInt(protocol);
    sendInt(modDeJeu+1);
	endProcess();
}

/*
 * Exécute le mouvement
 */
void Request::mov(std::string mov){
	waitForProcess();
    int protocol = 5;
	sendInt(protocol);
	sendStr(mov);
	endProcess();
}

/*
 * Requête d'abandon
 */
void Request::surrend(){
	waitForProcess();
	int protocol = 6;
	sendInt(protocol);
	endProcess();
}

/*
 * Requête d'envoi de message
 */
void Request::sendMessage(std::string name, std::string msg){
    waitForProcess();
    int protocol = 7;
    sendInt(protocol);
    sendStr(name);
    sendStr(msg);
    endProcess();
}

/*
 * Recoit un message
 */ 
void Request::recvMessage(){
    std::string name = recvStr();
    std::string msg = recvStr();
    endProcess();
    this->_client->recvMessage(name, msg);
}

/*
 * Requête d'ajout d'ami
 */
void Request::addFriend(std::string name){
    waitForProcess();
    int protocol = 8;
    sendInt(protocol);
    sendStr(name);
    endProcess();
}

/*
 * Requête de retrait d'ami
 */
void Request::removeFriend(std::string name){
    waitForProcess();
    int protocol = 9;
    sendInt(protocol);
    sendStr(name);
    endProcess();
}

/* 
 * Requête d'accepter un ami
 */
void Request::acceptFriend(std::string name, bool accept){
    waitForProcess();
    int protocol = 10;
    sendInt(protocol);
    sendStr(name);
    sendInt(static_cast<int>(accept)+1);
    endProcess();
}

/*
 * Accesseur de la liste d'amis
 */
void Request::getFriendList(){
    waitForProcess();
    int protocol = 11;
    sendInt(protocol);
    endProcess();
}

/*
 * Recevoir une demande d'ami
 */ 
void Request::getFriendRequests(){
    waitForProcess();
    int protocol = 12;
    sendInt(protocol);
    endProcess();
}

/*
 * recevoir les données d'un utilisateur, son elo etc
 */
void Request::getUserInfo(std::string username){
    waitForProcess();
    int protocol = 13;
    sendInt(protocol);
    sendStr(username);
    endProcess();
}

/*
 * Envoi demande partie avec ami
 */
void Request::gameWithFriends(std::string username, int gameMod){
    waitForProcess();
    int protocol = 14;
    sendInt(protocol);
    sendStr(username);
    sendInt(gameMod);
    endProcess();
}

void Request::putGRequest(){
    waitForProcess();
    std::string username = recvStr();
    int gameMod = recvInt();
    this->_client->getGRequests().push_back(std::make_pair(username, gameMod));
    endProcess();
}

void Request::exitQueue(){
    waitForProcess();
    int protocol = 16;
    sendInt(protocol);

    endProcess();
}

void Request::feedback(){
    int info = recvInt();
    std::string message = recvStr();
    endProcess();
    this->_client->feedback(info, message);
}

#endif