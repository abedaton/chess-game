#pragma once
#ifndef CLIENT_CPP
#define CLIENT_CPP

#include "../includes/client.hpp"

/*
 * Constructeur du client, prend en parametre son IP, un booléen disant s'il veut jouer en terminal ou en interface
 */
Client::Client(const char* ip, bool terminalMod, int argc, char** argv): _game(nullptr), _interface(nullptr){
	this->_server = new Request(this, ip);
	this->_affichageGui = !terminalMod;
	if (terminalMod){
		AbstractInterface* useless = new Terminal(this);
		(void)useless;
	} else {
		showGui(argc, argv);
	}
}

Client::~Client(){
	;;
}

std::vector<std::pair<std::string,int > >  Client::getGRequests(){
	return gameRequests;
}

/*
 * Setter de l'interface
 */
void Client::setInterface(AbstractInterface* interface){
	this->_interface = interface;
}


/*
 * Permet de lancer le matchmaking en fonction du mode de jeu
 */
void Client::waitForMatch(int gameMod){
	this->_gameMod = gameMod;
	this->_server->findMatch(gameMod);
}

/*
 * Lance une partie
 */
void Client::startingGame(bool playerTurn, std::string opponentName){
	Human* play_one;
	Human* play_two;
	if(this->_affichageGui){
		play_one = new SilencedHuman(this->_name, "francais");
		play_two = new SilencedHuman(opponentName, "francais");
	} else {
		play_one = new Human(this->_name, "francais");
		play_two = new Human(opponentName, "francais");
	}
	this->_game = new SuperGame(this->_gameMod, this, playerTurn, play_one, play_two);
	this->_interface->gameStart(opponentName);
}

/*
 * Applique le clic sur une case de l'interface
 */
void Client::click(std::string square){
	this->_game->click(square);
}

void Client::surrend(){
	this->_server->surrend();
}

/*
 * Effectue un mouvement 
 */
void Client::mov(std::string mov){
	std::cout << "mov for opponent: " << mov << std::endl;
	this->_server->mov(mov);
}

/*
 * ping l'interface pour afficher le move d'un adversaire
 */
void Client::opponentMov(std::string mov){
	int res = _game->opponentMov(mov);
	if (res == -1){
		this->lose();
	} else if (res == 1){
		this->win();
	}
}

/*
 * Indique que le client a gagné 
 */
void Client::win(){
	_interface->end(1);
	delete this->_game;
	this->_game = nullptr;
}

/*
 * Indique que le client a perdu
 */
void Client::lose(){
	_interface->end(2);
	delete this->_game;
	this->_game = nullptr;
}

/*
 * Indique que l'adversaire a abandonné
 */
void Client::opponentSurrend(){
	this->_interface->end(3);
	delete this->_game;
	this->_game = nullptr;
}

/*
 * Effectue un enregistrement d'un utilisateur, vérifie si les informations données sont correctes
 * @return true ou false si les informations sont correctes
 */
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

/*
 * Permet au client de se connecter au serveur 
 */
bool Client::login(std::string username,std::string password){
	if (username.empty() || password.empty()){
		return false;
	} else {
		this->_name = username;
		int res = _server->login(username,password);
		return static_cast<bool>(res);
	}
}

/*
 * Indique une erreur de connexion
 */
void Client::connectionError(){
	if (_interface != nullptr){
		this->_interface->connectionError();
	}
}


/*
 * Permet de quitter le jeu
 */
void Client::exit(){
	if (_interface != nullptr)
		delete this->_interface;
	if (_game != nullptr)
		delete _game;
	//delete _server;
	std::_Exit(0);
}

void Client::movPossibleUpdate(std::vector<std::pair<int,int> >* listMov){
	this->_interface->movPossibleUpdate(listMov);
}

/*
 * Envoie un message au serveur
 */
void Client::sendMessage(std::string name,std::string msg){
	if ((name != "") || (msg != "")){
		this->_server->sendMessage(name, msg);
	}
}

/*
 * Envoie au serveur la demande d'ami
 */
void Client::addFriend(std::string name){
	if (this->_name != name){
		this->_server->addFriend(name);
	}
}

/*
 * Envoie au serveur la demande de suppression d'ami
 */
void Client::removeFriend(std::string name){
	this->_server->removeFriend(name);
}

/*
 * Indique au serveur qu'on accepte la demande d'ami
 */
void Client::acceptFriend(std::string name, bool accept){
	this->_server->acceptFriend(name, accept);
}

/*
 * Recoit une demande d'ami du serveur
 */
void Client::getFriendRequests() {
	this->_server->getFriendRequests();
}

/*
 * Le client demande sa liste d'amis au serveur
 */
void Client::getFriendList(){
	this->_server->getFriendList();
}

/*
 * Le client demande ses infos au serveur (elo, rank etc)
 */
void Client::getUserInfo(){
	this->getUserInfo(this->_name);
}

/*
 * Le client demande des infos au serveur sur un autre joueur
 */
void Client::getUserInfo(std::string username){
	this->_server->getUserInfo(username);
}

/*
 * Le client recoit un message et l'envoie à l'interface
 */
void Client::recvMessage(std::string name, std::string msg){
	this->_interface->recvMessage(name, msg);
}

/*
 * Le client donne à l'interface la liste des requetes d'ami
 */
void Client::recvFriendRequestsList(std::vector<std::string> vec){
	this->_interface->recvFriendRequestsList(vec);
}

/*
 * Le client donne à l'interface la liste d'amis
 */
void Client::recvFriendList(std::vector<std::pair<std::string, bool> > frendList){
	this->_interface->recvFriendList(frendList);
}

/*
 * le client donne à l'interface les infos demandées
 */
void Client::recvInfo(std::string username, int nbrgames, int win, int elo){
	this->_interface->recvInfo(username, nbrgames, win, elo);
}

void Client::exitQueue(){
	this->_server->exitQueue();
}

void Client::feedback(int info, std::string message){
	this->_interface->feedback(info, message);
}

/*
 * Affiche l'interface graphique
 */
int Client::showGui(int argc, char** argv){
	QApplication app(argc, argv);
	this->_interface = new FenPrincipale(this);
    this->_interface->myShow();
    return app.exec(); 
}
#endif
