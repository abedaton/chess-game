# include "../includes/User.hpp"

//User::User(int client_sock) : Human("") ,_clientSock(client_sock){
//	pthread_t clientThread;
//    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
//}
User::User(int client_sock) :_clientSock(client_sock){
	this->_db = new Database();
	this->_match = new MatchMaking();
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}


// User::User(const User& user): Human(user), _clientSock(user._clientSock) {}
User::User(const User& user): _clientSock(user._clientSock) {}

//void User::startGame(AbstractGame* game, bool turn){
	
	//this->set_name("only_player");
	
	//this->launch_classic_game(this,this,"francais");
	
	//Game(this,this);
//}


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

void User::waitForMatch(){
    int gameMod = recvInt();
    //int elo = this->db->getElo(this->name));
    this->_match->waitForMatch(this, gameMod);
}

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
    pthread_exit(0);
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
        switch (protocol){
            case EXIT: //0
                this->exit();
                end = true;
                break;
            case REGISTER: //1
                this->letsRegister();
                break;
            case LOGIN: //2
                this->checkLogin();
                break;
            case PASS: //3
                break;
            case WAITFORMATCH: //4
                this->waitForMatch();
                break;    
           // case GETMOV: //5
           //     this->getMov();
           //     break;
           // case MOV: //6
           //     this->mov();
           //     break;
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
*/
