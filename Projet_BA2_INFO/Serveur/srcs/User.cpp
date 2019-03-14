# include "../includes/User.hpp"

User::User(int client_sock, Database* db, MatchMaking* match) : _clientSock(client_sock), _db(db), _match(match), _opponent(nullptr){
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

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
}

void User::surrend(){
    //To Do
}

void User::opponentMov(std::string mov){
    this->_myTurn = true;
    int protocol = 21;
    sendInt(protocol);
    sendStr(mov);
}

void User::sendMsg(std::string msg){
    int protocol = 22;
    sendInt(protocol);
    sendStr(msg);
}

void User::letsRegister() {
    std::string username = recvStr();
    std::string password = recvStr();
    std::string email = recvStr();

    if (this->_db->isUsernameFree(username)){
        this->_db->addUser(username, password, email);
        std::cout << "register successfull" << std::endl;
        this->name = username;
        this->sendInt(1);
        this->_db->createInfoTable(username, this->_clientSock);
    }
    else{
         this->sendInt(0);
    }
}

void User::checkLogin() {
    std::string username = recvStr();
    std::string password = recvStr();

    if (this->_db->isLoginOk(username,password)){
        this->name = username;
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
    this->_match->waitForMatch(this, gameMod);
}

void User::mov(){
    if (! this->_myTurn){ //hack
        std::cout << "should never happened" << std::endl;
        this->_opponent->surrend();
        this->exit();
    }
    std::string mov = recvStr();
    std::pair<bool,bool> pAnswer = this->_game->execute_step(mov, this->name);
    //std::pair<bool,bool> pAnswer = this->_game->execute_step(mov, this->name,this->get_inverted());
    if (std::get<0>(pAnswer)){
      this->_opponent->opponentMov(mov);
      this->_myTurn = false;
    }
    if (std::get<1>(pAnswer)){ //end
      this->_game = nullptr;
      ;;//To Do
    }
}



void User::exit() {
    close(this->_clientSock);
    std::cout << "exiting.." << std::endl;
    int i = 0;   
    bool found = false;
    
    //on enleve l'utilisateur du vector des joueurs connectés
    while(found == false && i < onlineUsers.size())
    {
        if(onlineUsers[i] != this)
            i++;
        else
            {
                found = true;
                onlineUsers.erase(onlineUsers.begin() + i);
            }
    }
    
    pthread_exit(0);
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
}

void User::addFriendToList(User *new_friend)
{
    friends.push_back(new_friend);
}

/*
normalement plus de (gros) bug prevenez moi (matias) si vous en trouvez
*/
void User::addFriend()
{
    std::string nameOfUserToAdd = recvStr();
    std::cout << name << " désire ajouter " << nameOfUserToAdd << std::endl;
    User* userToAdd = findUserByName(nameOfUserToAdd);
    if(userToAdd != nullptr)
    {
       sendInt(1);
       userToAdd->sendfriendRequestNotification(this);
       
    }
    else
        sendInt(0);

}

void User::recvFriendRequestAnswer()
{
    User *userAdding = findUserByName(recvStr());
    std::string answer = recvStr();
    if(userAdding)
    {
        if(answer == "y")
        {
            std::cout << "a accepte la requete de " << std::endl;
            userAdding->addFriendToList(this);
            this->addFriendToList(userAdding);
        }
    }
}

void User::sendfriendRequestNotification(User *userAdding)
{
    sendInt(NEWFRIENDREQUEST);
    sendStr(userAdding->getName());
}

void User::removeFromFriends(User *userToRemove)
{
    int i = 0;
    bool found = false;
    while(i < friends.size() && found == false)
    {
        if(friends[i] == userToRemove)
        {
            found = true;
            friends.erase(friends.begin() + i);
        }
        else
            i++;
    }
}

void User::removeFriend()
{
    std::string nameOfUserToDelete = recvStr();
    
    //on supprime dans les deux listes
    User *otherUser = findUserByName(nameOfUserToDelete);
    if(otherUser != nullptr)
    {
        sendInt(1);
        otherUser->removeFromFriends(this);
        removeFromFriends(otherUser);
        
    }
    else
        sendInt(0);
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
                this->mov();
                break;
            case LISTONLINEFRIENDS: 
                this->listOnlineFriends();
                break;
            case ADDFRIEND:
                addFriend();
                break;
            case REMOVEFRIEND:
                removeFriend();
                break;
            case FRIENDREQUESTANSWER:
                recvFriendRequestAnswer();
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

void User::updateInfo(){

}

bool User::get_inverted() const {return this->_isinverted;}
void User::set_inverted(bool inverted){this->_isinverted = inverted;}
