#pragma once
#ifndef SUPERGAME_CPP
#define SUPERGAME_CPP

#include "SuperGame.hpp"

SuperGame::SuperGame(int gameMod, AbstractPlayer* client, bool myTurn, std::string player1, std::string player2): _client(client), _inverted(!myTurn){
	Human* play_one = new Human(player1, player2);
	SilencedHuman* play_two = new SilencedHuman(player2, player1);
    Dico* dico = make_dico("Client/game/csv");
    BaseChess* game;

    int chessMod = gameMod%4;
	int partyMod = gameMod/4;
    
    AbstractAffichage* aff;
    if(chessMod == 1){
        aff = new AffichageDarkChess();
    }else{
        aff = new Affichage();
    }

    switch(chessMod){
        case 0:
            game = new ClassicChess(play_one, play_two, play_one, dico, aff);
            break;
        case 1:
            game = new DarkChess(play_one, play_two, play_one, nullptr, dico, aff);
            break;
        case 2:
            game = new TrappistChess(play_one, play_two, play_one, dico, aff);
            break;
        case 3:
            game = new AntiChess(play_one, play_two, play_one, dico, aff);
            break;
        default:
            game = new ClassicChess(play_one, play_two, play_one, dico, aff);
            break;
    }
    switch(partyMod){
        case 0:
            this->_game = new TourParTour(game);
            break;
        case 1:
            this->_game = new Pendule(game);
            break;
        case 2:
            this->_game = new TempsReel(game);
            break;
        default:
            this->_game = new TourParTour(game);
            break;
    }
}

bool SuperGame::click(std::string square){
    bool res = false;
    char* tmp = (char*)square.c_str();
    tmp[0] = std::toupper(tmp[0]);
    square = tmp;
	if(std::find(this->_ListMov.begin(), this->_ListMov.end(), square) != this->_ListMov.end()) {
        std::cout << "mov: " << this->_lastClick + ';' + square << std::endl; //TO DELETE
		res = this->turn(this->_lastClick + ';' + square);
		this->_lastClick = " ";
		_ListMov.clear();
	} else {
		this->_lastClick = square;
		this->_ListMov = *(this->_game->possible_mov(square) );
    }
    this->_client->movPossibleUpdate(this->_ListMov);
    return res;
}

bool SuperGame::turn(std::string mov){
	bool result = false;
    if (! this->_game->is_high_active()){
		this->_client->mov(mov);
        std::pair<bool, bool> res = this->_game->execute_step(mov, "player1", this->_inverted);
		if (res.second)
			result = true;
	} else {
		this->_bufferMov.push_back(mov);
	}
	return result;
}

int SuperGame::opponentMov(std::string mov){
    int result = 0;
    std::pair<bool, bool> res = this->_game->execute_step(mov, "player2",! this->_inverted);
    this->_ListMov.clear();
    this->_client->movPossibleUpdate(this->_ListMov);
	if (res.second)
		result = -1;
	else if (! this->_bufferMov.empty()){
		mov = this->_bufferMov.front();
		this->_bufferMov.erase(_bufferMov.begin());
        res = this->_game->execute_step(mov, "player1",! this->_inverted);
		if (! res.first) {
            this->_bufferMov.clear();
        } else if(res.second) {
            this->_client->movPossibleUpdate(this->_ListMov);
            result = 1;
        }
	}
	return result;
}

std::pair<bool, bool> SuperGame::serverMov(std::string mov, std::string username, bool inverted){
    if (! this->_game->is_high_active()){ //TO DO is_high_active 
        return this->_game->execute_step(mov, username, inverted);
    } else {
        return std::make_pair(false, false);
    }
}

Plateau* SuperGame::getBoard(){
    return this->_game->get_game()->get_plateau();
}

std::vector<std::string> SuperGame::getListMov(){

    return this->_ListMov;
}

#endif
