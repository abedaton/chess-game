# include "User.hpp"

User::User(int client_sock) : Human("") ,_clientSock(client_sock){
	pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

User::User(const User& user): Human(user), _clientSock(user._clientSock) {}

void* User::run(void* tmp){
    static_cast<User*>(tmp)->startGame();
    return NULL;
}

void User::startGame(){
	
	this->set_name("only_player");
	
	this->launch_classic_game(this,this,"francais");
	
	//Game(this,this);
}

void User::out(std::string str){
	sendInt(1);
	sendStr(str);
}

std::string User::in(){
	sendInt(2);
	return recvStr();
}

void User::exit() {
    close(this->_clientSock);
    std::cout << "exiting.." << std::endl;
    pthread_exit(0);
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
