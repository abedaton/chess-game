
#include "Serveur.hpp"

Serveur::Serveur(){}

Serveur::Serveur(std::string ip, short unsigned int port) : _ip(ip), _port(port) {
    this->db = new Database();
    this->match = new MatchMaking();
    this->setup();
}

void Serveur::setup(){
    this->_address.sin_family = AF_INET;
    this->_address.sin_port = htons(this->_port);
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_addrlen = sizeof(this->_address);

    if ((this->_serv_sock = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    } else {
        std::cout << "Socket created !" << std::endl;
    }

    if (bind(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), this->_addrlen) < 0){
        std::cout << "Error on bind: " << strerror(errno) << std::endl;
        this->sShutdown();
    } else {
        std::cout << "Bind successfull !" << std::endl;
    }

    if (listen(this->_serv_sock, 3) < 0){
        std::cout << "Error: " << strerror(errno) << std::endl;
        this->sShutdown();
    }

    this->mainLoop();
}

void Serveur::mainLoop(){
    std::thread cmdThread(&Serveur::handleCommand, *this);
    int tmpClient;
    while (true){
        if ((tmpClient = accept(this->_serv_sock, reinterpret_cast<struct sockaddr*>(&this->_address), reinterpret_cast<socklen_t*>(&this->_addrlen))) >= 0){
            std::cout << "Nouvelle connexion !" << std::endl;
            if (tmpClient != -1){
                int* socket;
                try {
                    if (*this->_clients.at(static_cast<unsigned long int>(tmpClient)) == -1){
                        this->_clients.at(static_cast<unsigned long int>(tmpClient)) = &tmpClient;
                        socket = _clients.at(static_cast<unsigned long int>(tmpClient));
                    }
                } catch (std::out_of_range& e) {
                    this->_clients.push_back(&tmpClient);
                    socket = _clients.at(static_cast<unsigned long int>(_clients.size()-1));
                }
                User us = User(socket, this->db, this->match, this);
            } else {
                std::cout << "Error.. socket == -1" << std::endl;
            }
        }
    }
}


void* Serveur::handleCommand(){
    std::string command;
    while (true) {
        getline(std::cin, command);
        if (command == "shutdown"){
            this->sShutdown();
            break;
        }
    }
    return NULL;
}


void Serveur::sShutdown(){
    sqlite3_close(this->db->getdb());
    shutdown(this->_serv_sock, SHUT_RDWR);
    for (unsigned long int i = 0; i < this->_clients.size(); i++){
        close(*this->_clients.at(i));
    }
    close(this->_serv_sock);
    std::cout << "Server is now offline." << std::endl;
    exit(EXIT_SUCCESS);
}


// ------------------------------ SERVEUR ------------------------------------------------------------------------------------

int Serveur::get_player_socket(std::string player_name){ // a implementer
	
	int sock;
	
	// conversion player_name: obtention de client_sock
	if (player_name == "player1"){sock = 0;} // exemple basique, le serveur connait les sockets des client, leur attribue un nom (qui donne au depart de lancement du jeu)
	else if (player_name == "player2"){sock = 1;}
	else{throw;}
	
	return sock;
	
}

void Serveur::kickClient(int sock){
	
	std::cout<<"socket kick_client"<<sock<<std::endl;
	
}

std::string Serveur::recvStr(int client_sock){
    uint16_t tmp_len_str;
    if (recv(client_sock, &tmp_len_str, sizeof(uint16_t), MSG_WAITALL) < 0){
        this->kickClient(client_sock);
    }
    uint16_t len_str = ntohs(tmp_len_str);
    std::vector<char> buffer(len_str);
    if (recv(client_sock, &buffer[0], buffer.size(), MSG_WAITALL) < 0){
        this->kickClient(client_sock);
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}

std::string Serveur::recvStr(std::string player_name){
	
	int sock = this->get_player_socket(player_name); // conversion player_name: obtention de client_sock
	return this->recvStr(sock);

}

void Serveur::sendStr(int client_socket, std::string msg){
	this->sendInt(msg.size(), client_socket);
    if (send(client_socket, msg.c_str(), msg.size(), 0) < 0){
        this->sShutdown();
    }
}

void Serveur::sendStr(std::string player_name, std::string msg){
	
	int sock = this->get_player_socket(player_name);
	this->sendStr(sock, msg);

}

void Serveur::sendInt(int num, int clientSock){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(clientSock, &convertedNum, sizeof(uint16_t), 0) < 0){
        this->sShutdown();
    }
}

Dico* make_dico(){
	
	Dico* dico = new Dico();
	
	std::string csv_path = "../../csv";
	std::string csv_filename = get_first_file_of_dir(csv_path,".csv");
	
	if (csv_filename == ""){throw MyException(&mout, "PAS DE FICHIER CSV! POUR LE DICTIONNAIRE");}
	
	std::stringstream ss;
	ss << csv_path << '/'<< csv_filename;
	
	dico->load(ss.str());
	
	return dico;

}

void Serveur::launch_classic_game(std::string langue){
	
	ServerMessage* msg = new ServerMessage(this);
	
	HumanServ* player_one = new HumanServ("player1",this);
	
	HumanServ* player_two = new HumanServ("player2",this);
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico();

	ClassicChess* classic_game = new ClassicChess(player_one,player_two,dico,langue,msg);
	
	classic_game->execute();
	
}

// ------------------------------ HUMANSERV ------------------------------------------------------------------------------------

HumanServ::HumanServ(std::string nom,Serveur* serv) : Human(nom), serveur(serv) {} //*< Constructor

HumanServ::HumanServ(const HumanServ& h_serv): Human(h_serv), serveur(h_serv.serveur) {}

Serveur* HumanServ::get_serveur(){return this->serveur;}

std::string HumanServ::next_input(){
	
	return this->get_serveur()->recvStr(this->get_name());
	
}

std::string HumanServ::get_type_prefix() const{
	return "HumanServ";
}


// ------------------------------ SERVERMESSAGE ------------------------------------------------------------------------------------

ServerMessage::ServerMessage(Serveur* serv) : serveur(serv){}

Serveur* ServerMessage::get_serveur(){return this->serveur;}

void ServerMessage::send_msg(Player* play,std::string msg, bool endline){
	
	std::string output;
	std::stringstream ss;
	
	if (endline == false){
		output = msg;
	}
	else{
		std::stringstream ss;
		ss<<msg<<std::endl;
		output = ss.str();
	}
	
	std::string nom_play = play->get_name();

	this->get_serveur()->sendStr(nom_play, output);
}

// -------------------------------------- USER -----------------------------------------------------------

User::User(int* client_sock, Database* db, MatchMaking* match, Serveur* serv) : _clientSock(client_sock), _db(db), _match(match), isLog(false), inGame(false), serveur(serv) {
    pthread_t clientThread;
    pthread_create(&clientThread, NULL, &User::run, static_cast<void*>(this));
}

void* User::run(void* tmp){
    static_cast<User*>(tmp)->handleClient();
    return NULL;
}

void User::handleClient(){
	while (true){
        int protocol = this->recvInt();
        if (protocol == 0) { // exit
            this->exit();
             break;
        } else if (protocol == 1){ // register
            this->letsRegister();
        } else if (protocol == 2){ // login
            this->checkLogin();
        } else if (protocol == 3){ // chat
            ;;
        } else if (protocol == 4){ // matchMaking
            this->waitForMatch();
        } else if (protocol == 5){ // getMov
            this->getMov();
        } else if (protocol == 6){ // Mov
            this->mov();
        } else if (protocol == 7){ // launch game
            this->serveur->launch_classic_game("francais");
            // "anglais" , "francais" , "neerlandais"
           // la langue française serait la langue par défault, peut-être le demander avant?
			// a terme le language sera lié au joueur --> permet d'avoir les affichages dans 2 langues différentes.
            
            
            
        }
        //...
    }
}

void User::exit() {
    close(*this->_clientSock);
    *this->_clientSock = -1;
    std::cout << "exiting.." << std::endl;
    pthread_exit(0);
}

void User::letsRegister() {
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
    this->_match->waitForMatch(this,gameMod);
}

void User::getMov(){
    std::string str = recvStr();
    std::string answear = this->_game->getMov(str);
    sendStr(answear);
}

void User::mov(){
    std::string str = recvStr();
    this->_game->mov(str);
}

void User::startGame(AbstractGame* game){
    this->_game = game;
    this->inGame = true;
}

void User::sendInt(int num){
    uint16_t convertedNum = htons(static_cast<uint16_t>(num));
    if (send(*this->_clientSock, &convertedNum, sizeof(uint16_t), 0) <= 0){
        std::cout << "Bad sentInt, client disconnected : " << std::endl;
        this->exit();
    }
}

int User::recvInt(){
    uint16_t Answer;
    if (recv(*this->_clientSock, &Answer, sizeof(uint16_t), MSG_WAITALL) <= 0){ 
        std::cout << "Bad recvInt, client disconnected : " << std::endl; 
        this->exit();
    }
    return ntohs(Answer);
}

void User::sendStr(std::string str){
    this->sendInt(static_cast<int>(str.size()));
    if (send(*this->_clientSock, str.c_str(), str.size(), 0) <= 0){
        this->exit();
    }
}

std::string User::recvStr(){
    int len_str = recvInt();
    std::vector<char> buffer(static_cast<long unsigned int>(len_str));
    if (recv(*this->_clientSock, &buffer[0], buffer.size(), MSG_WAITALL) <= 0){
        std::cout << "Bad recvStr, client disconnected : " << std::endl;
        this->exit();
    }
    std::string str(buffer.begin(), buffer.end());
    return str;
}



