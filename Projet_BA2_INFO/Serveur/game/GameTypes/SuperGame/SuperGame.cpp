#ifndef SUPERGAME_CPP
#define SUPERGAME_CPP

#include "SuperGame.hpp"

SuperGame::SuperGame(int gameMod, AbstractPlayer* client, bool myTurn): _client(client), _inverted(!myTurn), _lastClick(""){
	SilencedHuman* play_one = new SilencedHuman("player1", "francais");
	SilencedHuman* play_two = new SilencedHuman("player2", "francais");
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
	if(std::find(this->_ListMov.begin(), this->_ListMov.end(), square) != this->_ListMov.end()) {
		res = this->turn(this->_lastClick + ';' + square);
		this->_lastClick = "";
		_ListMov.clear();
	} else {
		this->_lastClick = square;
        Chesspiece* pe = this->_game->get_plateau()->get_piece(this->_game->str_mov_to_int(square)).get_var();
		std::vector<std::pair<int,int> > tmp = *this->_game->get_game()->check_all_mov(pe);
        this->_ListMov.clear();
        std::string tmp2;
        for (auto& i : tmp){
            tmp2 = static_cast<char>((i.first + 65));
            this->_ListMov.push_back(tmp2 + std::to_string(i.second));
        }
	}
    return res;
}

bool SuperGame::turn(std::string mov){
    if (! this->_game->is_high_active()){
		this->_client->mov(mov);
        std::pair<bool, bool> res = this->_game->execute_step(mov, "player1", this->_inverted);
		if (res.second)
			return true;
	} else {
		this->_bufferMov.push_back(mov);
	}
}

bool SuperGame::opponentMov(std::string mov){
    std::pair<bool, bool> res = this->_game->execute_step(mov, "player2",! this->_inverted);
	if (res.second)
		return true;
	else if (! this->_bufferMov.empty()){
		mov = this->_bufferMov.front();
		this->_bufferMov.erase(_bufferMov.begin());
        res = this->_game->execute_step(mov, "player1",! this->_inverted);
		if (res.first) {
			this->turn(mov);
        } else {
			this->_bufferMov.clear();
        }
	}
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
