#include "../includes/client.hpp"

Client::Client(){
	this->_request = new Request(this);
	firstWindow();
}

Client::~Client(){
	std::cout << "Destructor" << std::endl;
}

void Client::connectionError(){
	std::cout << "Connection with server lost : " << strerror(errno) << std::endl;
	//delete this; // :(
}

void Client::startingGame(bool playerTurn){
	std::cout << "Game is starting. Please press a random key to continue" << std::endl;
	this->_myTurn = playerTurn;
	this->_gameStart = true;

	Dico* dico = make_dico("Client/game/csv"); // path of the executable
	Player* player1 = new Human(this->_username,"francais");
	Player* player2 = new Human("Opponent","francais");
	switch (this->_gameMod){
		case 1:
			if (playerTurn) {
				this->_game = new ClassicChess(player1, player2, dico);
			} else {
				this->_game = new ClassicChess(player2, player1, dico);
			}
			break;
		case 2:
			//this->_game = new ClassicChess();
			break;
		case 3:
			//this->_game = new ClassicChess();
			break;
		case 4:
			//this->_game = new ClassicChess();
			break;
		default:
			break;
	}
}

void Client::opponentMov(std::string mov){
	this->_game->execute_step(mov, "Opponent");
	this->_myTurn = true;
}

void Client::recvMessage(){
	;;//to do
}

void Client::firstWindow(){
	bool log = false;
	bool exit = false;
	char answer;
	while(! log && !exit){
		answer = ' ';
		while ( answer != '1' && answer != '2' && answer != '3' ) {
			std::cout << "Write 1 for login, 2 for register or 3 for exit:" << std::endl;
			std::cin >> answer;
			this->myFlush();
		}
		if (answer == '1')
			log=logInWindow();
		else if (answer == '2')
			log=registerWindow();
		else
			exit = true;
	}
	if (! exit){
		menuWindow();
	}
}

bool Client::registerWindow(){
    std::string username;
    std::string password;
    std::string password2;
    std::string email;
    std::regex regEmail("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\\])");
    while(true){
        std::cout << "Write your new username: ";
        std::cin >> username;
        myFlush();
        std::cout << "Write your email: ";
        std::cin >> email;
        myFlush();
        password = getpass("New password (will not be shown): ");
        password2 = getpass("New password (again): ");
        if (password != password2){
            std::cout << "Password does not match!" << std::endl;
            continue;
        
		}
        if (! std::regex_match(email.begin(), email.end(), regEmail)){
			std::cout << "Invalid email." << std::endl;
			continue;
        }
		if (this->_request->letsRegister(username,password,email)){
			std::cout << "You are now logged in !" << std::endl;
			this->_username = username;
			return true;
		}
		else{
			char answer;
			std::cout << "Invalide Username.\n Write 1 for continue or 2 to go back: ";
			std::cin >> answer;
			this->myFlush();
			while (answer != '1' && answer != '2'){
				std::cout << "Please write 1 for continue or 2 to go back: ";
				std::cin >> answer;
				this->myFlush();
			}
			if (answer == '2')
				return false;
		}
    }
}

bool Client::logInWindow(){
	std::string username;
    std::string password;
    while(true){
        std::cout << "Write your username :";
        std::cin >> username;
        this->myFlush();
        password = getpass("Password (password will not be shown) :");
        if(this->_request->login(username,password)){
			std::cout << "You are now logged in !" << std::endl;
			this->_username = username;
			return true;
		}
		else{
			char answer;
			std::cout << "Invalid username or password." << std::endl;
			std::cout << "Write 1 for continue or 2 to go back: ";
			std::cin >> answer;
			myFlush();
			while (answer != '1' && answer != '2'){
				std::cout << "Please write 1 for continue or 2 to go back: ";
				std::cin >> answer;
				myFlush();
			}
			if (answer == '2')
				return false;
		}
    }
}

void Client::menuWindow(){
	char answer;
	bool waitForGame = false;
    while (true){
        std::cout << "Enter 1 for exit, 2 for chat";
		if (!waitForGame)
			std::cout <<", 3 for game";
		std::cout << ": " << std::endl;
        std::cin >> answer;
		myFlush();
		if (this->_gameStart){
			gameWindow();
			waitForGame = false;
		} else{
        	if (answer == '1'){
        	    break;
        	}
        	else if (answer == '2'){
        	    ;;// To Do
        	}
        	else if (answer == '3' && !waitForGame){
        	    waitForGame = selectGameModeWindow();
        	}
		}
    }
}

bool Client::selectGameModeWindow(){
	char answer;
    std::cout << "Enter 1 for classic, 2 for Dark, 3 for Trappist, 4 for Anti or 5 for return to the menu: " << std::endl;
    std::cin >> answer;
	myFlush();
    while (answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5'){
        std::cout << "Please, enter 1 for classic, 2 for Dark, 3 for Trappist, 4 for Anti or 5 for return to the menu: " << std::endl;
        std::cin >> answer;
		myFlush();
    }
	if (answer == '5')
		return false;
	else{
		this->_gameMod = atoi(&answer);
		this->_request->findMatch(this->_gameMod);
		return true;
	}
}

void Client::gameWindow(){
	int answer;
	std::pair<bool, std::string> returnP;
    while (true){
        std::cout << "Enter 1 for surrender, 2 for chat, 3 for play" << std::endl;
        std::cin >> answer;
		myFlush();
		if (answer == 1){
			//this->_request->surrend(); //petit bug embaitemps
            break;
        }
        else if (answer == 2){
            ;;
        }
        else if (answer == 3){
			if (this->_myTurn){
				returnP = this->_game->execute_step();
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
}

void Client::myFlush(){
    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
