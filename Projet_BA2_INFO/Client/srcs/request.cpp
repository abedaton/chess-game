#include "../includes/request.hpp"

Request::Request(AbstractClient* client, const char* ip): _client(client){
	setup(ip);
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

void Request::removeFriend(std::string name)
{
    waitForProcess();
    sendInt(REMOVEFRIEND);
    sendStr(name);

    int res = recvInt();
    if(res == 0)
        std::cout << "L'utilisateur à supprimer n'a pas été trouvé " << std::endl;
    else
        std::cout << "L'utilisateur a correctement été supprimé" << std::endl;
    endProcess();

}

void Request::proceedGameAndFriendRequests()
{
    std::cout << "Vous avez " << friendRequests.size() << " demandes d'amis " << std::endl;
    while(friendRequests.size() > 0)
    {
        FriendRequests newPotentialFriend = friendRequests.front();
        friendRequests.pop();
        
        std::cout << newPotentialFriend.name << " souhaite vous ajouter en ami: " << std::endl;
        char res = 0;
        while(res != 'y' && res != 'n')
        {
            std::cout << "veuillez appuyer sur y pour l'accepter, n pour le refuser: ";
            std::cin >> res;
        }

        
        sendInt(FRIENDREQUESTANSWER);
        sendStr(newPotentialFriend.name);
        char toSend[2] = {0, 0};
        
        toSend[0] = res;
        sendStr(toSend);
    }
    
}


bool Request::listOnlineFriends()
{
    waitForProcess();
    sendInt(LISTONLINEFRIENDS);
    int friendsOnline = recvInt();
  
    std::cout << "Vous avez: " << friendsOnline <<  "ami(s) en ligne" << std::endl; 
    for(int i = 0; i < friendsOnline; i++)
        std::cout << recvStr() << " est en ligne " << std::endl;
    
    endProcess();
    return true;
}

/*
Retourne vrai/faux selon le fait que l'utilisateur existe ou pas.
l'autre client (qu'on ajoute) doit aller dans le menu consulter 
mes demandes d'amis pour l'accepter et le serveur se charge du reste.
*/
bool Request::addFriend(std::string name)
{
    waitForProcess();
    sendInt(ADDFRIEND);
    sendStr(name);
    std::cout << "Vous avez ajouté: \"" << name << "\" à votre liste d'amis veuillez attendre sa réponse" << std::endl;
    bool res = recvInt();
    std::cout << "res was :" << res ;
    endProcess();
    return res;
}

//todo thread safe friendRequests?
void Request::recvFriendAddNotification()
{
    FriendRequests newPotentialFriend;
    newPotentialFriend.name = recvStr();
    friendRequests.push(newPotentialFriend);
}



//////////////////////////////////////////////////////////////////////////////////////////////PRIVIET
void Request::setup(const char* ip){
    this->_servAddr.sin_addr.s_addr	= inet_addr(ip);
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
            case (NEWFRIENDREQUEST):
                recvFriendAddNotification();
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
    int inverted = recvInt();
	int ennemy_inverted = recvInt();
	std::string ennemy_name = recvStr();
	
	this->_client->set_inverted(static_cast<bool>(inverted-1));
	this->_client->set_ennemy_inverted(static_cast<bool>(ennemy_inverted-1));
	this->_client->set_ennemy_name(ennemy_name);
	
	//j'ai préféré mettre les setters en dehors plustôt que de tout mettre dans startgame, a vous de choisir -quentin.
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