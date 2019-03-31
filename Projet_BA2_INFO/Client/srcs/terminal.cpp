#pragma once
#ifndef TERMINAL_CPP 
#define TERMINAL_CPP 

#include "../includes/terminal.hpp"

/*
 * Constructeur de l'objet terminal
 * Permet l'affichage en mode terminal des fonctionnalités et du jeu
 */
Terminal::Terminal(AbstractClient* client): _user(client), _gameStart(false), _end(false) { 
	client->setInterface(this);
	this->_mut = new std::mutex;
	this->_mut->lock();
	firstWindow();
}

/*
 * Destructeur 
 */
Terminal::~Terminal(){
	std::cout << "Destructor" << std::endl;
}

/*
 * Indique une erreur de connexion avec le serveur et quitte
 */
void Terminal::connectionError(){
	std::cout << "\nConnection with server lost : " << strerror(errno) << std::endl;
	this->_user->exit();
	//exit(EXIT_FAILURE);
}

/*
 * Affiche sur le terminal que le jeu commence
 */
void Terminal::gameStart(std::string opponent){
	this->_ennemyName = opponent;
	this->_gameStart = true;
    std::cout << "\nGame is starting. Please press a random key to continue" << std::endl;
}

void Terminal::movPossibleUpdate(std::vector<std::pair<int,int> >* listMov){
	std::cout << "updateBord" << std::endl;
    //To Do
}

/*
 * Affiche que le joueur a gagné sa partie et termine la partie
 */
void Terminal::win(){
	std::cout << "you won" << std::endl;
	this->_end = true;
}

/*
 * Affiche que le joueur a perdu sa partie et termine la partie
 */ 
void Terminal::lose(){
	std::cout << "you lost" << std::endl;
	this->_end = true;
}

/*
 * Affiche le menu liste d'amis
 */
void Terminal::friendsWindow(){
	unsigned int res = 0;
	std::string username;
	std::string message;
	std::string tmpanswer;
	bool answer;
	while(res != 9){
		std::cout << "\nQue désirez vous faire?: " << std::endl;
		std::cout << "1) Ajouter un ami " << std::endl;
		std::cout << "2) Lister tous les amis " << std::endl;
		std::cout << "3) Supprimer un ami " << std::endl;
		std::cout << "4) Consulter mes demandes d'amis" << std::endl;
		std::cout << "5) Accepter une demandes d'amis" << std::endl;
		std::cout << "6) Proposer à un ami de faire une partie " << std::endl;
		std::cout << "7) Chat avec des amis " << std::endl;
		std::cout << "8) Voir les stats d'un joueur " << std::endl;
		std::cout << "9) Retourner au menu principal " << std::endl;

		res = 0;
		while(res == 0 || res > 9){	
			std::cout << "Enter a number(1-9): ";
			std::cin >> res;
			this->myFlush();
		}
		switch(res){
			case 1:
				std::cout<< "Veuillez entrer le nom de l'ami à ajouter: ";
				std::cin >> username;
				
				this->_user->addFriend(username);
				break;
			case 2:
				this->_user->getFriendList();
				this->_mut->lock();
				break;
			case 3:
				std::cout << "Veuillez entrer le nom de l'ami à supprimer: ";
				std::cin >> username;
				this->_user->removeFriend(username);
				break;
			case 4:
				this->_user->getFriendRequests();
				this->_mut->lock();
				break;
			case 5:
				std::cout<< "Veuillez entrer le nom de l'ami pour réponde à sa demande d'amis: ";
				std::cin >> username;
				this->myFlush();
				if(std::find(this->_friendRequest.begin(), this->_friendRequest.end(), username) == this->_friendRequest.end()){
					std::cout << "Cette personne ne vous à pas demandé en ami" << std::endl;
					break;
				}
					
				std::cout << "Acceptez vous ça demande d'amis(yes, no): ";
				std::cin >> tmpanswer;
				this->myFlush();
				if ((tmpanswer == "yes") || (tmpanswer == "Yes") || (tmpanswer == "nope'nt") || (tmpanswer == "y") || (tmpanswer == "Y")){
					answer = true;
				} else if((tmpanswer == "no") || (tmpanswer == "No") || (tmpanswer == "yes'nt") || (tmpanswer == "n") || (tmpanswer == "N")){
					answer = false;
				} else {
					std::cout << "Invalid input" << std::endl;
					break;
				}
				this->_user->acceptFriend(username, answer);
				break;
			case 6:
				// 1. call listonlinefriends pour montrer tous les amis disponibles
				// 2. laiser l'utilisateur choisir l'ami puis l'inviter à la partie
				break;
			case 7:
				std::cout << "Please enter the name of the user you want to send a message: ";
				std::getline(std::cin, username);
				std::cout << "Please enter your message: ";
				std::getline(std::cin, message);
				this->_user->sendMessage(username, message);
				std::cout << "Message Sent!" << std::endl; // Todo check if user exists
				break;
			case 8:
				std::cout << "Please enter the name of the user you want to see de stat: ";
				std::getline(std::cin, username);
				this->_user->getUserInfo(username);
				this->_mut->lock();
				break;
		}
	}
}


/*
 * Premier affichage au lancement du client
 */
void Terminal::firstWindow(){
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
	} else {
		this->_user->exit();
	}
}

/*
 * Affichage de l'inscription au jeu
 */ 
bool Terminal::registerWindow(){
    std::string username;
    std::string password;
    std::string password2;
    std::string email;
	while(true){
        std::cout << "Write your new username: ";
        std::cin >> username;
        myFlush();
        std::cout << "Write your email: ";
        std::cin >> email;
        myFlush();
        password = getpass("New password (will not be shown): ");
        password2 = getpass("New password (again): ");
       
		if (this->_user->letsRegister(username, password, password2, email)){
			std::cout << "You are now logged in !" << std::endl;
			this->_username = username;
			return true;
		} else {
			char answer;
			std::cout << "Write 1 for continue or 2 to go back: ";
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

/*
 * Affichage de l'interface de connexion
 */
bool Terminal::logInWindow(){
	std::string username;
    std::string password;
    while(true){
        std::cout << "Write your username :";
        std::cin >> username;
        this->myFlush();
        password = getpass("Password (password will not be shown) :");
        if(this->_user->login(username,password)){
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

/*
 * Affiche le menu principal
 */
void Terminal::menuWindow(){
	char answer;
	bool waitForGame = false;
    while (true){
        std::cout << "Enter 1 for exit 2 for friend list 3 to see your stat 4 to see if someone wants to play with you";
		if (!waitForGame)
			std::cout <<", 5 for game";
		else 
			std::cout <<", 5 exit queue";
		std::cout << ": ";
        std::cin >> answer;
		myFlush();
		if (this->_gameStart){
			_gameStart = false;
			gameWindow();
			waitForGame = false;
		} else{
        	if (answer == '1'){
        	    break;
        	} else if (answer == '2'){
        	    friendsWindow();
        	} else if (answer == '3'){
        	    this->_user->getUserInfo();
				this->_mut->lock();
			}else if (answer == '4'){
				if(this->_user->getGRequests().size() == 0){
					std::cout << "Personne ne veut jouer avec vous." << std::endl;
				}else{
					std::vector<std::pair<std::string,int> > liste;
					std::cout << "Liste du/des joueur(s) qui veut/lent jouer avec vous : " << std::endl;
					for(int cnt = 0; cnt < liste.size(); cnt++){
						std::cout << cnt << " " << liste[cnt].first << "en gameMod " << liste[cnt].second;
					}
					std::cout << "Entrez le numéro du joueur avec qui vous voulez jouer ou -1 si vous voulez quitter." << std::endl;
					int name;
					std::cin >> name ;
					this->myFlush();
					while(name >= liste.size() || name < -1){
						std::cout << "Entrez un nommbre correct entre -1 et " << liste.size() -1 << " " << std::endl; 
					}
					if(name != -1){
						
						//this->_user->gameStart(name, gameMod);
						//this->_user->;;
						;;
					}

				}
        	} else if (answer == '5' && !waitForGame){
        	    waitForGame = selectGameModeWindow();
        	} else if (answer == '5' && waitForGame){
				this->_user->exitQueue();
				waitForGame = false;
			}
		}
    }
}

/*
 * Affiche un message recu par le chat
 */
void Terminal::recvMessage(std::string username, std::string msg){
	if (username == this->_ennemyName) {
		std::cout << "\nYour opponent(" << username << "): " << msg << std::endl;
	} else {
		std::cout << "\n" << username << ": " << msg << std::endl;
	}
}

/*
 * Affiche la fenetre de sélection du mode de jeu
 */
bool Terminal::selectGameModeWindow(){
	std::string chessMod = " ";
	std::string gameMod = " ";

    while (chessMod != "1" && chessMod != "2" && chessMod != "3" && chessMod != "4" && chessMod != "5"){
        std::cout << "Please, enter 1 for classic, 2 for Dark, 3 for Trappist, 4 for Anti or 5 for return to the menu: ";
        std::cin >> chessMod;
		myFlush();
    }
	if (chessMod == "5")
		return false;
	while (gameMod != "1" && gameMod != "2" && gameMod != "3" && gameMod != "4"){
        std::cout << "Enter 1 for Tour Par tour, 2 for Chrono, 3 for Temps Reel, 4 for return to the menu: ";
        std::cin >> gameMod;
		myFlush();
    }
	if (gameMod == "4")
		return false;
	else { 
		this->_chessMod = std::stoi(chessMod)-1;
		int tmp = this->_chessMod + (4 * (std::stoi(gameMod)-1)); //chessMod + (4 * gameMod)
		this->_user->waitForMatch(tmp);
		return true;
	}
}

/*
 * Affichage principal en pleine partie
 */
void Terminal::gameWindow(){
	int answer;
	std::string square;
    while (true){
        std::cout << "Enter 1 for surrender, 2 for chat, 3 for click on the bord: ";
        std::cin >> answer;
		myFlush();
		if (_end){
			std::cout << "lose" << std::endl;
			this->_end = false;
			break;
		}
		if (answer == 1){
			//this->_user->surrend(); 
            break;
        } else if (answer == 2) {
            std::string msg = "coucou";
			std::cout << "Enter a message for your opponent: " << std::endl;
			//std::cin.clear();
        	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, msg);
			//this->myFlush();
			this->_user->sendMessage(this->_ennemyName, msg);
        } else if (answer == 3) {
			
			std::cout << "Choose a square" << std::endl;
			std::cin >> square;
			this->myFlush();
			std::regex regClick;
			if (this->_chessMod != 2){ 
				regClick.assign("^[a-hA-H][1-8]$");
			} else {
				regClick.assign("^[a-xA-X][1-24]$");
			}
			if (std::regex_match(square.begin(), square.end(), regClick))
				_user->click(square);
			else
				std::cout << "Wrong input, it needs to be a square (ex: A4)" << std::endl;
			
        }
    }
}

/*
 * Affiche les demandes d'amis 
 */
void Terminal::recvFriendRequestsList(std::vector<std::string> vec){
	this->_friendRequest = vec;
	if (vec.size() > 0){
		std::cout << "You have " << vec.size() << " pending requests: " << std::endl;
		for (unsigned i = 0; i < vec.size(); i++){
			std::cout << "\t- " << vec[i] << std::endl;
		}
	} else {
		std::cout << "You have no pending requests.. :(" << std::endl;
	}
	this->_mut->unlock();
}

/*
 * Affiche la liste d'amis reçue
 */
void Terminal::recvFriendList(std::vector<std::pair<std::string, bool> > frendList){
	this->_friendList = frendList;
	if (frendList.size() > 0){
		std::cout << "You have " << frendList.size() << " friends: " << std::endl;
		for (unsigned i = 0; i < frendList.size(); i++){
			std::cout << "\t- " << frendList[i].first << ": " << (frendList[i].second ? "connected" : "disconnected") << std::endl;
		}
	} else {
		std::cout << "Sorry you dont have any friend.. :(" << std::endl;
	}
	this->_mut->unlock();
}

/*
 * Affiche les infos sur un joueur
 */
void Terminal::recvInfo(std::string username, int nbrGames, int win, int elo){
	if (username == this->_username){
		this->_info.nbrGames = nbrGames;
		this->_info.win = win;
		this->_info.elo = elo;
	}
	double ratio = 100;
	if(nbrGames-win != 0){
		ratio = (static_cast<float>(win)/static_cast<float>(nbrGames))*100.0;
	}
	std::string rank;
	if (elo < 1000)
		rank = "bronze";
	else if (elo < 1700)
		rank = "argent";
	else
		rank = "or";

	std::cout << username << " stat:" << std::endl;	
	std::cout << "\t-nbrGames: " << nbrGames << std::endl;
	std::cout << "\t-win: " << win << std::endl;
	std::cout << "\t-lose: " << nbrGames-win << std::endl;
	std::cout << "\t-Ratio: " << ratio << "\%" << std::endl;
	std::cout << "\t-Elo(n Musk): " << elo << std::endl;
	std::cout << "\t-rank: " << rank << std::endl;
	this->_mut->unlock();
}

/*
 * Nettoie un string
 */
void Terminal::myFlush(){
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Terminal::feedback(int info, std::string message){
	(void)info;
	std::cout << std::endl << message << std::endl;
	this->_mut->unlock();
}



#endif
