# include "User.hpp"

//User::User(int client_sock) : Human("") ,_clientSock(client_sock){
//	pthread_t clientThread;
//    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
//}
User::User(int client_sock) :_clientSock(client_sock){
	this->_db = new    Database();
	this->_match = new MatchMaking();
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}


// User::User(const User& user): Human(user), _clientSock(user._clientSock) {}
User::User(const User& user): _clientSock(user._clientSock) {}

void User::startGame(AbstractGame* game, bool turn){
	
	//this->set_name("only_player");
	
	//this->launch_classic_game(this,this,"francais");
	
	//Game(this,this);
}


void User::letsRegister() {
    std::cout << "letsRegister" << std::endl;
    std::string username = recvStr();
    std::string password = recvStr();
    std::string email = recvStr();

    if (this->_db->isUsernameFree(username)){
        this->_db->addUser(username, password, email);
        std::cout << "register successfull" << std::endl;
        this->name = username;
        this->isLog = true;
        this->sendInt(1);
    }
    else{
         this->sendInt(0);
    }
}

void User::checkLogin() {
    std::cout << "checking login" << std::endl;
    std::string username = recvStr();
    std::string password = recvStr();

    if (this->_db->isLoginOk(username,password)){
        std::cout << "yup" << std::endl;
        this->name = username;
        this->isLog = true;
        this->sendInt(1);
    } else {
        std::cout << "nope" << std::endl;
        this->sendInt(0);
    }
}

void User::chat(){
    ;;
}

/*
void User::waitForMatch(){
    int gameMod = recvInt();
    //int elo = this->db->getElo(this->name));
    //this->_match->waitForMatch(this, gameMod);
}*/

void User::out(std::string str){
	sendInt(30);
	sendStr(str);
}

std::string User::in(){
	sendInt(31);
	return recvStr();
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
}



std::string User::getName()
{
    return name;
}


//------------------------------------------------------------------------------
//toutes les fonctions par rapport a la liste d'amis implémentées ici:
//------------------------------------------------------------------------------
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

    /*std::string answer = recvStr();
    if(answer == "y")
    {
        std::cout << "a accepte la requete de " << std::endl;
        userAdding->addFriendToList(this);
        this->addFriendToList(userAdding);
        //sauvgarder dans la bdd ici ?
    }

    std::cout << name << "  left sendfriendRequestNotification" <<std::endl;*/
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

//juste une fonction debug utilisée à fin de ne pas avoir à register des nouveaux utilisateurs, a ignorer
void User::dbgSetName()
{
    name = recvStr();
    std::cout << "name was received" << name.c_str() << std::endl;
    std::cout << name.c_str() << "just connected \n " << std::endl;
}



//Privet

void* User::run(void* tmp){
    static_cast<User*>(tmp)->handleClient();
    return NULL;
}



void User::handleClient(){
    std::cout << "handleClient" << std::endl;
    bool end = false;
    Protocol protocol;
    while (true){
        protocol = static_cast<Protocol>(this->recvInt());
        std::cout << "protocol received: " << protocol << " from: " << name << std::endl;
        switch (protocol){
            case EXIT: //0
                this->exit();
                end = true;
                break;
            case REGISTER: //1
                this->letsRegister();
                break;
            case LOGIN: //2
                //this->checkLogin();
                dbgSetName();
                break;
            case PASS: //3
                break;
            case WAITFORMATCH: //4
                //this->waitForMatch();
                break;    
           // case GETMOV: //5
           //     this->getMov();
           //     break;
           // case MOV: //6
           //     this->mov();
           //     break;
            
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
        if (end){
            break;
        }
    }
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

void User::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

/*
std::string User::recvStr(){
    int len_str = recvInt(); //probleme avec ce code si len_str est negatif ca va crash le serveur non? 
    std::cout << "length is :" << len_str << std::endl;
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->exit();
    }
    

    std::string str(buffer.begin(), buffer.end());
    return str;
}
*/

std::string User::recvStr()
{
    std::string res;
    int size = this->recvInt();
    if(size > 0)
    {
        char *str = new char[size+1];
        std::memset(str, 0, size+1);

        if(recv(this->_clientSock, str, size, MSG_WAITALL) <= 0)
        {   
            this->exit();
        }

        res = str;
        delete[] str;
    }
    else{
        res = "error";
    }
    
    return res;
}

//------------------------
/*
void User::launch_classic_game(User* player_one,User* player_two, std::string langue){
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico("../../csv");
	
	(void) player_two;
	
	Bot* bot_player = make_bot("player2","bot_un","../../bots_csv");
	
	mout<<(*bot_player)<<std::endl;

	ClassicChess* classic_game = new ClassicChess(player_one,bot_player,dico,langue);
	
	classic_game->execute();
	
}


std::string User::next_input(){
	
	//std::cout<<"IN"<<std::endl;
	
	return this->in();
	
}

std::string User::get_type_prefix() const{
	
	//std::cout<<"PREFIX"<<std::endl;
	
	return "User";
}

void User::send_confirm_msg(std::string msg, bool endline){
	
	std::string output = this->msg_compaction(msg,endline);
		
	this->out(output);
}
*/