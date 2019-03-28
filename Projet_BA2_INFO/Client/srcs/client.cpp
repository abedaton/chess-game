#ifndef CLIENT_CPP
#define CLIENT_CPP

<<<<<<< HEAD
Client::Client(const char* ip){
	this->_request = new Request(this, ip);
	firstWindow();
=======
#include "../includes/client.hpp"
#include "../../Gui/incl/FenPrincipale.hpp"

Client::Client(const char* ip, bool terminalMod, int argc, char** argv): _game(nullptr), _interface(nullptr){
	this->_server = new Request(this, ip);
	if (terminalMod){
		AbstractInterface* useless = new Terminal(this);
		(void)useless;
	} else {
		showGui(argc, argv);
	}
>>>>>>> Partie_Serveur
}


Client::~Client(){
	;;
}

void Client::setInterface(AbstractInterface* interface){
	this->_interface = interface;
}

<<<<<<< HEAD
void Client::startingGame(bool playerTurn){
	std::cout << "Game is starting. Please press a random key to continue" << std::endl;
	this->_myTurn = playerTurn;
	this->_gameStart = true;

	Dico* dico = make_dico("Client/game/csv"); // path of the executable
	Player* player1 = new Human(this->_username,"francais");
	Player* player2 = new Human(this->get_ennemy_name(),"francais");
	
	// serie de players crée pour simplifier le switch
	Player* low_player;
	Player* high_player;
	Player* begin_player;
	
	if (playerTurn){
		begin_player = player1;
		
		// si commence jamais inversé normalement -quentin
		low_player = player1;
		high_player = player2;
	}
	
	else{
		begin_player = player2;
		
		if (this->get_inverted()){
			low_player = player1;
			high_player = player2;
		}
		
		else{
			low_player = player2;
			high_player = player1;
		}
	}
	
	BaseChess* game_mode;
	switch (this->_gameMod){
		case 1:
			game_mode = new ClassicChess(low_player, high_player, begin_player, dico);
			break;
			
		case 2:
			game_mode = new DarkChess(low_player, high_player, begin_player, player1, dico);
			break;
			
		case 3:
			game_mode = new TrappistChess(low_player, high_player, begin_player, dico);
			break;
			
		case 4:
			game_mode = new AntiChess(low_player, high_player, begin_player, dico);
			break;
			
		default:
			std::cout << "error" << std::endl;
			break;
	}
	this->_game = new TourParTour(game_mode); // plustard pemettre de choisir entre "tour par tour", "temps reel" et "pendule" -quentin
}

void Client::opponentMov(std::string mov){
	
	try{this->_game->execute_step(mov, this->get_ennemy_name(),this->get_inverted() != this->get_ennemy_inverted());} //this->get_inverted()
	catch(MyException& e){
		std::cout << e.what()<<std::endl;
		std::cout << "myexception catched"<<std::endl;
		this->connectionError(); // ??? <-------------------------------- correct façon d'arreter le jeu? -quentin
	}
	
	this->_myTurn = true;
}
=======
void Client::waitForMatch(int gameMod){
	this->_gameMod = gameMod;
	this->_server->findMatch(gameMod);
}

>>>>>>> Partie_Serveur

void Client::startingGame(bool playerTurn, std::string opponentName){
	this->_game = new SuperGame(this->_gameMod, this, playerTurn);
	this->_interface->gameStart(opponentName);//+ bord
}

void Client::click(std::string square){
	this->_game->click(square);
}

void Client::mov(std::string mov){
	this->_server->mov(mov);
	this->_interface->pingForUpdate();
}

void Client::opponentMov(std::string mov){
	bool res = _game->opponentMov(mov);
	_interface->pingForUpdate();
	if (res){
		this->lose();
	}
}

void Client::win(){
	_interface->win();
	delete this->_game;
	this->_game = nullptr;
}

void Client::lose(){
	_interface->lose();
	delete this->_game;
	this->_game = nullptr;
}

bool Client::letsRegister(std::string username,std::string password1, std::string password2, std::string email){
	std::string error;
	bool answer = false;
	std::regex regEmail("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\\])");
	if (username.empty() || password1.empty()){
		error = "Please fill in all fields";
	} else if (! std::regex_match(email.begin(), email.end(), regEmail)){
		error = "Invalid email";
	} else if(password1 != password2){
		error = "Password doesn't match";
	} else {
		error = "Success";
		this->_name = username;
		answer = static_cast<bool>(_server->letsRegister(username, password1, email));
	}
	return answer; //pair
}

bool Client::login(std::string username,std::string password){
	if (username.empty() || password.empty()){
		return false;
	} else {
		this->_name = username;
		int res = _server->login(username,password);
		return static_cast<bool>(res);
	}
}

void Client::connectionError(){
	if (_interface != nullptr){
		this->_interface->connectionError();
	}
}

void Client::exit(){
	//if (_interface != nullptr) --------------------------------------------------------- // !!! enleve warning (classe abstraite)
	//	delete this->_interface;
	if (_game != nullptr)
		delete _game;
	delete _server;
	try {
		delete this; //:(
	} catch(std::exception& e){
		;;
	}
}

//bool Client::get_inverted() const{}
//void Client::set_inverted(bool){}
//
//bool Client::get_ennemy_inverted() const{}
//void Client::set_ennemy_inverted(bool){}

void Client::movPossibleUpdate(std::vector<std::string> listMov){
	//TO DO
	(void)listMov;
}

void Client::sendMessage(std::string name,std::string msg){
	if( (name != "") || (msg != "") )
		this->_server->sendMessage(name, msg);
}
void Client::addFriend(std::string name){
	if (this->_name != name){
		this->_server->addFriend(name);
	}
}
void Client::removeFriend(std::string name){
	this->_server->removeFriend(name);
}
void Client::acceptFriend(std::string name, bool accept){
	this->_server->acceptFriend(name, accept);
}
void Client::getFriendRequests() {
	this->_server->getFriendRequests();
}
void Client::getFriendList(){
	this->_server->getFriendList();
}

<<<<<<< HEAD
void Client::gameWindow(){
	int answer;
	std::pair<bool, std::string> returnP;
    while (true){
        std::cout << "Enter 1 for surrender, 2 for chat, 3 for play" << std::endl;
        std::cin >> answer;
		myFlush();
		if (answer == 1){
			//this->_request->surrend(); 
            break;
        }
        else if (answer == 2){
            std::string msg;
			std::cout << "Enter a message for your opponent: \n" << std::endl;
			std::cin.clear();
        	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, msg);
			this->myFlush();
			this->_request->chat(msg);
        }
        else if (answer == 3){
			if (this->_myTurn){
				try{returnP = this->_game->execute_step();}
				catch(MyException& e){
					std::cout << e.what()<<std::endl;
					std::cout << "myexception catched"<<std::endl;
					break; // ??? <-------------------------------- correct façon d'arreter le jeu? -quentin
				}
				
				this->_request->mov(std::get<1>(returnP));
				if(std::get<0>(returnP)){
					std::cout << "END" << std::endl;
				 	break;
				}
				this->_myTurn = false;
			} else{
				std::cout << "It is not your turn" << std::endl;
			}
        }
    }
=======
void Client::getUserInfo(){
	this->getUserInfo(this->_name);
}

void Client::getUserInfo(std::string username){
	this->_server->getUserInfo(username);
}
void Client::recvMessage(std::string name, std::string msg){
	this->_interface->recvMessage(name, msg);
>>>>>>> Partie_Serveur
}
void Client::recvFriendRequestsList(std::vector<std::string> vec){
	this->_interface->recvFriendRequestsList(vec);
}
void Client::recvFriendList(std::vector<std::pair<std::string, bool> > frendList){
	this->_interface->recvFriendList(frendList);
}
void Client::recvInfo(std::string username, int nbrgames, int win, int elo){
	this->_interface->recvInfo(username, nbrgames, win, elo);
}


int Client::showGui(int argc, char** argv){
	QApplication app(argc, argv);
	this->_interface = new FenPrincipale(this);
    this->_interface->myShow();
    return app.exec(); 
}
<<<<<<< HEAD

bool Client::get_inverted() const {return this->_isInverted;}
void Client::set_inverted(bool inverted){this->_isInverted = inverted;}

bool Client::get_ennemy_inverted() const {return this->_isEnnemyInverted;}
void Client::set_ennemy_inverted(bool inverted){this->_isEnnemyInverted = inverted;}

std::string Client::get_ennemy_name() const {return this->_ennemyName;}
void Client::set_ennemy_name(std::string name){this->_ennemyName = name;}
=======
#endif
>>>>>>> Partie_Serveur
