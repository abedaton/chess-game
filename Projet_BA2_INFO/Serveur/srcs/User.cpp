# include "../includes/User.hpp"

User::User(int client_sock, Database* db, MatchMaking* match) : _clientSock(client_sock), _db(db), _match(match), _opponent(nullptr){
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

<<<<<<< HEAD
void User::startGame(TempsReel* game, AbstractUser* oppenent, bool turn, bool inverted,bool ennemy_inverted, std::string ennemy_name){
    this->_game = game;
    this->_opponent = oppenent;
    this->_myTurn = turn;
    this->set_inverted(inverted);
	int protocol = 20;
    sendInt(protocol);
    sendInt(static_cast<int>(turn)+1);
    sendInt(static_cast<int>(inverted)+1);
    sendInt(static_cast<int>(ennemy_inverted)+1); //this->get_ennemy_inverted() ? (startgame player2 apres -> non?)
    sendStr(ennemy_name); //this->get_ennemy_name()
    std::cout << "startGame" << std::endl;
=======
User::~User(){
    std::cout << "destructor" << std::endl;
    exit();
>>>>>>> Partie_Serveur
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
    std::cout << "gamemod = " << gameMod << std::endl;
    int elo = _db->getInt(this->_name, "elo");
    this->_match->waitForMatch(this, gameMod, elo);
}
<<<<<<< HEAD
        
void User::mov(){
    if (! this->_myTurn){ //hack
        std::cout << "should never happened" << std::endl;
        this->_opponent->surrend();
        this->exit();
    }
    std::string mov = recvStr();
    
    std::pair<bool,bool> pAnswer = this->_game->execute_step(mov, this->name,this->get_inverted());
    if (std::get<0>(pAnswer)){
      this->_opponent->opponentMov(mov);
=======

void User::recvMov(){
    std::string mov = recvStr();
    this->mov(mov);
}

void User::mov(std::string mov){
    std::pair<bool, bool> pAnswer = this->_game->serverMov(mov, this->_name,this->_inverted);
    if (pAnswer.first){
      this->_opponent->sendMov(mov);
>>>>>>> Partie_Serveur
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
    
<<<<<<< HEAD
    this->_db->updateUserDisc(this->name);
    pthread_exit(0);
}

std::string User::get_name() const{return this->name;}

std::string User::getName()
{
    return this->name;
}

User* User::findUserByName(std::string name)
{
    User * res = nullptr;
    int i = 0;
    while(i < onlineUsers.size() && res == nullptr)
    {
        if(name == onlineUsers[i]->getName())
            res = onlineUsers[i];
        i++;
    }
    return res;
}


/*
note findUserByName est un mauvais moyen pour trouver si un joueur est toujours en ligne
je pense que ce serait mieux de juste supprimer de la variable membre friends
 au fur et à mesure qu'un joueur se deconnecte
*/
void User::listOnlineFriends()
{
    sendInt(friends.size());
    for(int i = 0; i < friends.size(); i++)
    {
        if(findUserByName(friends[i]->getName()) != nullptr) //on regarde si il est toujours en ligne
            sendStr(friends[i]->getName());
    }
=======
    this->_db->updateUserDisc(this->_name);
    pthread_exit(0);
}

std::string User::get_name() const{
    return this->_name;
>>>>>>> Partie_Serveur
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
            case GETUSERINFO: // 13
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

<<<<<<< HEAD
}

bool User::get_inverted() const {return this->_isinverted;}
void User::set_inverted(bool inverted){this->_isinverted = inverted;}
=======
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

void User::sendMessage(){
    int protocol = 28;
    std::string username = recvStr();
    std::string msg = recvStr(); // messgae du user1 vers user2
    int friendSocket = this->_db->getUserInt("socket", username);
    if (friendSocket >= 0){
        sendIntToSocket(friendSocket, protocol);
        sendStrToSocket(friendSocket, this->_name);
        sendStrToSocket(friendSocket, msg);
    } else {
        // Todo send Feedback User no exists
    }
} 


/////////////////////////////////////////////////////////////////////
void User::addFriend(){
    std::string user = recvStr();
    bool result = this->_db->sendFriendRequest(this->_name, user);
    if (!result){
        // TODO send feedback user no exists
    }
}

void User::removeFriend(){
    std::string username = recvStr();
    this->_db->deleteFriend(this->_name, username);
}

void User::acceptFriend(){
    std::string user = this->recvStr();
    bool answer = (this->recvInt()-1) ? 1 : 0;
    this->_db->acceptFriend(this->_name, user, answer);
}

void User::getFriendRequests(){
    int protocol = 29;
    std::vector<std::string> friendList = this->_db->seeFriendRequests(this->_name);
    sendInt(protocol);
    sendVector(friendList);
}

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

void User::GetUserInfo(){
    std::string username;
    username = recvStr();
    int protocol = 31;
    int games = this->_db->getInt(username, "nbrGames");
    int win = this->_db->getInt(username, "win");
    int elo = this->_db->getInt(username, "elo");
    sendInt(protocol);
    sendStr(username);
    sendInt(games);    
    sendInt(win);
    sendInt(elo);
}
>>>>>>> Partie_Serveur
