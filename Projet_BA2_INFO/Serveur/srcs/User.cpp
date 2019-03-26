# include "../includes/User.hpp"

User::User(int client_sock, Database* db, MatchMaking* match) : _clientSock(client_sock), _db(db), _match(match), _opponent(nullptr){
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

User::~User(){
    std::cout << "destructor" << std::endl;
    exit();
}


void User::surrend(){
    //To Do
}


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

void User::chat(){
    std::string msg = recvStr();
    this->_opponent->sendMsg(msg);
}

void User::waitForMatch(){
    int gameMod = recvInt();
    int elo = _db->getInt(this->_name, "elo");
    this->_match->waitForMatch(this, gameMod, elo);
}

void User::recvMov(){
    std::string mov = recvStr();
    this->mov(mov);
}

void User::mov(std::string mov){
    std::pair<bool, bool> pAnswer = this->_game->serverMov(mov, this->_name,this->_inverted);
    if (pAnswer.first){
      this->_opponent->sendMov(mov);
      this->_myTurn = false;
    } else {
        this->_opponent->surrend();
        this->exit();
    } if (pAnswer.second){ //end
        this->_game = nullptr;
        this->_db->updateWin(this->_name, this->_opponent->get_name(), true);
        this->_opponent->lose();
        std::cout << "Score updated for " << this->_name << std::endl;
    }
}

void User::lose(){
    this->_game = nullptr;
    this->_db->updateWin(this->_name, this->_opponent->get_name(), false);
}


void User::exit() {
    close(this->_clientSock);
    std::cout << "exiting.." << std::endl;
    int i = 0;   
    bool found = false;
    
    //on enleve l'utilisateur du vector des joueurs connectés
    
    this->_db->updateUserDisc(this->_name);
    pthread_exit(0);
}

std::string User::get_name() const{
    return this->_name;
}


//Privet

void* User::run(void* tmp){
    static_cast<User*>(tmp)->handleClient();
    return NULL;
}

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
            case GETONLINEFRIENDLIST: // 13
                this->getOnlineFriendList();
                break;
            case GETMYINFO: // 14
                this->getMyInfo();
                break;
            case GETUSERINFO: // 15
                this->GetUserInfo();
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

void  User::waitForProcess(){
    this->_mutex.lock();
}

void  User::endProcess(){
    this->_mutex.unlock();
}


void User::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

int User::recvInt(){
    uint16_t Answer;
    if (recv(this->_clientSock, &Answer, sizeof(uint16_t), MSG_WAITALL) <= 0){ 
        std::cout << "Bad recvInt, client disconnected : " << strerror(errno) << std::endl; 
        this->exit();
    }
    return ntohs(Answer);
}

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

void User::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

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

void User::sendStrToSocket(int socket, std::string str){
    this->sendIntToSocket(socket, static_cast<int>(str.size()));
    if (send(socket, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

void User::sendIntToSocket(int socket, int number){
    uint16_t convertedNum = htons(static_cast<uint16_t>(number));
    if (send(socket, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

void User::startGame(SuperGame* game, AbstractUser* oppenent, bool turn){
	int protocol = 25;
    this->_game = game;
    this->_opponent = oppenent;
    this->_myTurn = turn;
    this->_inverted = ! turn;
    sendInt(protocol);
    sendInt(static_cast<int>(turn)+1);
    sendStr(oppenent->get_name());
    std::cout << "startGame" << std::endl;
}

void User::sendMov(std::string mov){
    int protocol = 26;
    this->_myTurn = true;
    sendInt(protocol);
    sendStr(mov);
}

void User::sendMsg(std::string msg){
    int protocol = 27;
    sendInt(protocol);
    sendStr(msg);
}

void User::sendMessage(){
    std::cout << "Transfering Message" << std::endl;
    int protocol = 28;
    std::string username = recvStr();
    std::string msg = recvStr(); // messgae du user1 vers user2
    int friendSocket = this->_db->getInt("users", "socket");
    sendIntToSocket(friendSocket, protocol);
    sendStrToSocket(friendSocket, msg);
} 

void User::addFriend(){

}

void User::removeFriend(){

}

void User::acceptFriend(){

}

void User::getFriendList(){

}

void User::getFriendRequests(){

}

void User::getOnlineFriendList(){

}

void User::getMyInfo(){

}

void User::GetUserInfo(){

}
