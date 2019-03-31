#pragma once
#ifndef USER_CPP
#define USER_CPP
# include "../includes/User.hpp"

/*
 * Constructeur du user
 */
User::User(int client_sock, Database* db, MatchMaking* match) : _clientSock(client_sock), _db(db), _match(match), _opponent(nullptr), _waitForGame(false){
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

/*
 * Destructeur, fait quitter le client
 */
User::~User(){
    std::cout << "destructor" << std::endl;
    exit();
}


/*
 * Applique l'inscription d'un utilisateur
 */
void User::letsRegister() {
    std::string username = recvStr();
    std::string password = recvStr();
    std::string email = recvStr();

    if (this->_db->isUsernameFree(username)){
        this->_db->addUser(username, password, email, this->_clientSock);
        std::cout << "register successfull" << std::endl;
        this->_name = username;
        this->sendInt(1);
        this->_db->createInfoTable(username);
    }
    else{
         this->sendInt(0);
    }
}

/*
 * Vérifie si le nom d'utilisateur et le mot de passe sont correspondants
 */
void User::checkLogin() {
    std::string username = recvStr();
    std::string password = recvStr();

    if (this->_db->isLoginOk(username,password)){
        this->_name = username;
        this->sendInt(1);
        this->_db->updateUserLog(username, this->_clientSock);
    } else {
        this->sendInt(0);
    }
}

/*
 * Envoie un message du chat à son adversaire
 */
void User::chat(){
    std::string msg = recvStr();
    this->_opponent->sendMsg(msg);
}

/*
 * Met l'utilisateur dans le matchmaking
 */
void User::waitForMatch(){
    this->_waitForGame = true;
    int gameMod = recvInt()-1;
    this->_gameMod = gameMod;
    int elo = _db->getInt(this->_name, "elo");
    this->_match->waitForMatch(this, gameMod, elo);
}

/*
 * Reçoit un move de l'utilisateur
 */
void User::recvMov(){
    std::string mov = recvStr();
    this->mov(mov);
}

/*
 * Exécute un move et update les scores en cas de victoire ou défaite
 */
void User::mov(std::string mov){
    std::cout << "serverMov: " << mov << std::endl;
    std::pair<bool, bool> pAnswer = this->_game->serverMov(mov, this->_name,this->_inverted);
    std::cout << "answer from game: " << pAnswer.first << std::endl;
    if (pAnswer.first){
        this->_opponent->sendMov(mov);
    } else {
        this->_opponent->opponentSurrend();
        this->exit();
    } if (pAnswer.second){ //end
        this->_game = nullptr;
        this->_db->updateWin(this->_name, this->_opponent->get_name(), true);
        this->_opponent->lose();
        std::cout << "Score updated for " << this->_name << std::endl;
    }
}

/*
 * Permet d'indiquer qu'un joueur a perdu
 */
void User::lose(){
    this->_game = nullptr;
    this->_db->updateWin(this->_name, this->_opponent->get_name(), false);
}

/*
 * Permet d'indiquer que l'adversaire a quitté la partie
 */
void User::opponentSurrend(){
    this->_db->updateWin(this->_name, this->_opponent->get_name(), true);
    //to do
}

/*
 * Fait quitter le client
 */
void User::exit() {
    if(this->_waitForGame){
        int elo = _db->getInt(this->_name, "elo");
        this->_match->exitQueue(this,this->_gameMod, elo);
    }
    close(this->_clientSock);
    std::cout << "exiting.." << std::endl;
    int i = 0;   
    bool found = false;
    
    //on enleve l'utilisateur du vector des joueurs connectés
    
    this->_db->updateUserDisc(this->_name);
    pthread_exit(0);
}

/*
 * Getter du nom de l'utilisateur
 */
std::string User::get_name(){
    return this->_name;
}


//Privet

/*
 * Lance handle client dans son thread
 */
void* User::run(void* tmp){
    static_cast<User*>(tmp)->handleClient();
    return NULL;
}

/*
 * Méthode qui va boucler pour attendre les demandes du client
 */
void User::handleClient(){
    bool end = false;
    Protocol protocol;
	while (true){
        waitForProcess();
        protocol = static_cast<Protocol>(this->recvInt(MSG_DONTWAIT));
        switch (protocol){
            case PASS: //0
                break;
            case REGISTER: //1
                this->letsRegister();
                break;
            case LOGIN: //2
                this->checkLogin();
                break;
            case CHAT: //3
                this->chat();
                break;
            case WAITFORMATCH: //4
                this->waitForMatch();
                break;    
            case MOV: //5
                this->recvMov();
                break;
            case SURREND: // 6
                this->_opponent->opponentSurrend();
                lose();
                break;
            case SENDMESSAGE: // 7
                this->sendMessage();
                break;
            case ADDFRIEND: // 8
                this->addFriend();
                break;
            case REMOVEFRIEND: // 9
                this->removeFriend();
                break;
            case ACCEPTFRIEND: // 10
                this->acceptFriend();
                break;
            case GETFRIENDLIST: // 11
                this->getFriendList();
                break;
            case GETFRIENDREQUESTS: // 12
                this->getFriendRequests();
                break;
            case GETUSERINFO: // 13
                this->GetUserInfo();
                break;
            
            case LEAVEQUEUE: // 16
                this->exitQueue();
                break;

            default:
                this->exit();
                end = true;
                break;
        }
        endProcess();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if (end){
            break;
        }
    }
}

/*
 * Lock le mutex
 */
void  User::waitForProcess(){
    this->_mutex.lock();
}

/*
 * Delock le mutex
 */
void  User::endProcess(){
    this->_mutex.unlock();
}


/*
 * Envoie un entier
 */
void User::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

/*
 * Recoit un entier
 */
int User::recvInt(){
    uint16_t Answer;
    if (recv(this->_clientSock, &Answer, sizeof(uint16_t), MSG_WAITALL) <= 0){ 
        std::cout << "Bad recvInt, client disconnected : " << strerror(errno) << std::endl; 
        this->exit();
    }
    return ntohs(Answer);
}

/*
 * Recoit un entier, le flag permet de savoir si on est en wait all ou pas
 */
int User::recvInt(int flag){
    uint16_t Answer;
    int res = recv(this->_clientSock, &Answer, sizeof(uint16_t), flag);
    if (res > 0){
        return ntohs(Answer);
    } else if (res < 0){
        return 0;
    } else {
        this->exit();
    }
}

/*
 * Permet d'envoyer un string
 */
void User::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

/*
 * Permet de recevoir un string
 */ 
std::string User::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->exit();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}

/*
 * Envoie un string à la socket
 */
void User::sendStrToSocket(int socket, std::string str){
    this->sendIntToSocket(socket, static_cast<int>(str.size()));
    if (send(socket, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

/*
 * Envoie un entier à la socket
 */
void User::sendIntToSocket(int socket, int number){
    uint16_t convertedNum = htons(static_cast<uint16_t>(number));
    if (send(socket, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

/*
 * Lance une partie
 */
void User::startGame(SuperGame* game, AbstractUser* oppenent, bool turn){
	int protocol = 25;
    this->_waitForGame = false;
    this->_game = game;
    this->_opponent = oppenent;
    this->_inverted = !turn;
    sendInt(protocol);
    sendInt(static_cast<int>(turn)+1);
    sendStr(oppenent->get_name());
    std::cout << "startGame" << std::endl;
}

/*
 * Envoie un move
 */
void User::sendMov(std::string mov){
    int protocol = 26;
    sendInt(protocol);
    sendStr(mov);
}

/*
 * Envoie un message
 */ 
void User::sendMsg(std::string msg){
    int protocol = 27;
    sendInt(protocol);
    sendStr(msg);
}

/*
 * Envoie un vecteur
 */
void User::sendVector(std::vector<std::string> vec){
    long length = htonl( vec.size());
    send(this->_clientSock, &length, sizeof(length), 0);
    //sendInt(vec.size);
    for (int i = 0; i < vec.size(); ++i) {
        //sendInt(vec[i].length());
        length = htonl( vec[i].length());
        send(this->_clientSock, &length, sizeof(length), 0);
        //sendStr(vec[i].data());
        send(this->_clientSock, vec[i].data(), vec[i].length(), 0);
    }
}

/*
 * Envoie un message
 */
void User::sendMessage(){
    int protocol = 28;
    std::string username = recvStr();
    std::string msg = recvStr(); // messgae du user1 vers user2
    int friendSocket = this->_db->getUserInt("socket", username);
    if (friendSocket >= 0){
        sendIntToSocket(friendSocket, protocol);
        sendStrToSocket(friendSocket, this->_name);
        sendStrToSocket(friendSocket, msg);
    } else if (friendSocket == -2){
        this->feedback(2, "This user doesn't exists !");
     } else {
        this->feedback(2, "This user is offline !");
     }
} 


/////////////////////////////////////////////////////////////////////
/*
 * Ajoute un ami 
 */
void User::addFriend(){
    std::string user = recvStr();
    bool result = this->_db->sendFriendRequest(this->_name, user);
    if (!result){
        this->feedback(1, "Cet utilisateur n'existe pas");
    }
}

/*
 * Retire un ami
 */
void User::removeFriend(){
    std::string username = recvStr();
    this->_db->deleteFriend(this->_name, username);
}

/*
 * Accepte un ami et l'ajoute à la liste
 */
void User::acceptFriend(){
    std::string user = this->recvStr();
    bool answer = (this->recvInt()-1) ? 1 : 0;
    this->_db->acceptFriend(this->_name, user, answer);
}

/*
 * Recoit les demandes d'amis
 */
void User::getFriendRequests(){
    int protocol = 29;
    std::vector<std::string> friendList = this->_db->seeFriendRequests(this->_name);
    sendInt(protocol);
    sendVector(friendList);
}

/* 
 * Recoit la liste d'ami
 */
void User::getFriendList(){
    int protocol = 30;
    std::vector<std::string> friendList = this->_db->seeFriends(this->_name);
    friendList.erase(std::remove(friendList.begin(), friendList.end(), this->_name), friendList.end());
    sendInt(protocol);
    sendInt(friendList.size()+1);
    for (auto userName : friendList){
        sendStr(userName);
        int tmp = this->_db->getUserInt("loggedIn", userName);
        sendInt(tmp+1);
    }
}

/*
 * Recoit les infos sur un utilisateur
 */
void User::GetUserInfo(){
    std::string username;
    username = recvStr();
    int protocol = 31;
    int games = this->_db->getInt(username, "nbrGames");
    if (games != -2){
        int win = this->_db->getInt(username, "win");
        int elo = this->_db->getInt(username, "elo");
        sendInt(protocol);
        sendStr(username);
        sendInt(games);
        sendInt(win);
        sendInt(elo);
    } else {
        this->feedback(3, "No user named " + username +"\n");
    }
}

void User::gameWithFriends(){
    std::string username;
    username = recvStr();
    int gameMod = recvInt();
    int protocol = 32;
    int friendSocket = this->_db->getUserInt("socket", username);
    if (friendSocket >= 0){
        sendIntToSocket(friendSocket, protocol);
        sendStrToSocket(friendSocket, username);
        sendIntToSocket(friendSocket, gameMod);
    }
    //this->getGRequests();//.pushback(username);
    
}

void User::exitQueue(){
    int elo = this->_db->getInt(this->_name, "elo");
    this->_match->exitQueue(this, this->_gameMod, elo);
}

void User::feedback(int info, std::string message){
    int protocol = 33;
    sendInt(protocol);
    sendInt(info);
    sendStr(message);
}

#endif