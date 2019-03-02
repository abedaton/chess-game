#include "client.hpp"


Client::Client(){
	this->_request = new Request(); //pq dynamiquement ?
	//firstWindow();
}

//pour aller plus vite dans les tests
void Client::Run(std::string n )
{
	std::cout<< "sending:" << n << std::endl;
	_request->login(n,"ignore");
	firstWindow();
}





Client::~Client(){
	std::cout << "Destructor"  << std::endl;
	//delete this->_requests; ???????
}

void Client::connectionError(){
	std::cout << "Connection with server lost : " << strerror(errno) << std::endl;
	delete this; // :(
}

void Client::startingGame(bool playerTurn){
	this->_gameStart = true;
	//this->_myTurn = playerTurn;
}

void Client::opponentMov(int coord1, int coord2, bool lose){
	;;//to do
}



void Client::firstWindow(){
	
	friendsWindow();
}


/*
void Client::firstWindow(){
	bool log = false;
	bool exit = false;
	char answer;
	while(! log && !exit){
		while ( answer != '1' && answer != '2' ) {
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
*/


void Client::listOnlineFriends()
{
	_request->listOnlineFriends();
}


//use mutex pour voir liste d'amis
void Client::friendsWindow()
{
	unsigned int res = 0;
	
	while(res != 7)
	{
		std::cout << "Que désirez vous faire?: " << std::endl;
		std::cout << "1) Ajouter un ami " << std::endl;
		std::cout << "2) Lister tous les amis connectés " << std::endl;
		std::cout << "3) Supprimer un ami " << std::endl;
		std::cout << "4) Consulter mes demandes d'amis/de parties " << std::endl;
		std::cout << "5) Proposer à un ami de faire une partie " << std::endl;
		std::cout << "6) Chat avec des amis " << std::endl;
		std::cout << "7) Retourner au menu principal " << std::endl;

		std::cin >> res;
		while(res == 0 || res > 7)
		{	
			std::cout << "Choix invalide veuillez réessayer:" << std::endl;
			std::cin >> res;
		}
		

		
		if(res == 1)
		{
			std::string friendName;
			std::cout<< "Veuillez entrer le nom de l'ami à ajouter: ";
			std::cin >> friendName;
			if(!_request->addFriend(friendName))
				std::cout << friendName << " n'existe pas " << std::endl;
			else
				std::cout<< "La demande d'ami a été envoytée" << std::endl;	
		}

		else if(res == 2)
		{			
			_request->listOnlineFriends();
		}	

		else if(res == 3)
		{
			std::string friendName;
			std::cout<< "Veuillez entrer le nom de l'ami à supprimer: ";
			std::cin >> friendName;
			_request->removeFriend(friendName);
		}
		else if(res == 4)
		{
			//todo implementer une mutex ? car on ne peut pas faire 2 cin en meme temps donc oblige 
			//de sleep pour recevoir les requetes du serveur
			
			/*
			std::cout << "écrivez \"exit\" pour revenir au menu" <<std::endl;
			std::string tmp;
			while(tmp != "exit")
				std::cin >> tmp;*/
			//std::this_thread::sleep_for(std::chrono::milliseconds(10000));
			_request->proceedGameAndFriendRequests();
		}		
			
		else if(res ==5)
		{
			/*
			1. call listonlinefriends pour montrer tous les amis disponibles
			2. laiser l'utilisateur choisir l'ami puis l'inviter à la partie
			*/

		}

		else if(res ==6)
			;
			
		else if(res == 7)
			;

		else
			std::cout << "Choix invalide veuillez réessayer:" << std::endl;
			
		
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
		if (this->_request->letsRegister(username,password,email))
			return true;
		else{
			char answer;
			std::cout << "Write 1 for continue or 2 for exit: ";
			std::cin >> answer;
			while (answer != '1' && answer != '2'){
				std::cout << "Please write 1 for continue or 2 for exit: ";
				std::cin >> answer;
			}
			if (answer != '2')
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
			return true;
		}
		else{
			char answer;
			std::cout << "Invalid username or password." << std::endl;
			std::cout << "Write 1 for continue or 2 for exit: ";
			std::cin >> answer;
			while (answer != '1' && answer != '2'){
				std::cout << "Please write 1 for continue or 2 for exit: ";
				std::cin >> answer;
			}
			if (answer != '2')
				return false;
		}
    }
}

void Client::menuWindow(){
	char answer;
	bool waitForGame = false;
    while (true){
		if (this->_gameStart){
			gameWindow();
			waitForGame = false;
		}
        std::cout << "Enter 1 for exit, 2 for chat";
		if (!waitForGame)
			std::cout <<", 3 for game";
		std::cout << ": " << std::endl;
        std::cin >> answer;
		myFlush();
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
		this->_request->findMatch(static_cast<int>(answer));
		;;//set bord
		return true;
	}
}

void Client::gameWindow(){
//	//this->_lose = false;
//	std::string answer;
//    std::vector<int> listMov;
//	int coord1;
//	int coord2;
//    while (true){
//        std::cout << "Enter 1 for surrend, 2 for chat, 3 for checkmov";
//        if (! listMov.empty())
//                std::cout << ", 4 for mov";
//        std::cout << std::endl;
//        std::cin >> answer;
//		myFlush();
//        if (strcmp(answer.c_str(),"1")){
//			this->_request->surrend();
//            break;
//        }
//        else if (strcmp(answer.c_str(),"2")){
//            ;;
//        }
//        else if (strcmp(answer.c_str(),"3") && this->_myTurn){ //getMov
//			std::cout << "Enter the letter of the colomne and the number of the line (ex: 'B3'): ";
//			std::cin >> answer;
//			myFlush();
//			//if ( check with regex ){
//				//coord1 = convertStringToCoord(answer);
//				//listMov = this->_request->getMov(coord);
//			//}
//        }
//        else if(!listMov.empty() && strcmp(answer.c_str(),"4") && this->_myTurn){ //mov
//			coord2 = -1;
//			while (std::find(listMov.begin(), listMov.end(), coord2) != listMov.end()){
//				std::cout << "Enter the letter of the colomne and the number of the line (ex: 'B3'): ";
//				std::cin >> answer;
//				myFlush();
//				//coord2 = convertStringToCoord(answer);
//			}
//			this->_myTurn = false;
//			//this->_bord->updateMov();
//			this->_request->mov(coord1,coord2);
//        }
//		else{
//			std::cout << "Please wait your turn." << std::endl;
//		}
//    }
}

void Client::myFlush(){
    if (std::cin.fail()){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}