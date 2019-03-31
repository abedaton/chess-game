#pragma once
#ifndef SUPERGAME_CPP
#define SUPERGAME_CPP

#include "SuperGame.hpp"

SuperGame::SuperGame(int gameMod, AbstractPlayer* client, bool myTurn, Player* play_one, Player* play_two): _client(client){
    //this->_inverted = !myTurn;
    this->_player1 = play_one->get_name();
    this->_player2 = play_two->get_name();
    this->_lastClick = " ";

    Dico* dico = make_dico("game/csv");
    BaseChess* game;

    int chessMod = gameMod%4;
	int partyMod = gameMod/4;
    
    AbstractAffichage* aff;
    if(chessMod == 1){
        aff = new AffichageDarkChess();
    }else{
        aff = new Affichage();
    }

    Player* first;
    if (myTurn){
        first = play_one;
    } else {
        first = play_two;
    }

    switch(chessMod){
        case 0:
            game = new ClassicChess(play_one, play_two, first, dico, aff);
            break;
        case 1:
            game = new DarkChess(play_one, play_two, first, play_one, dico, aff);
            break;
        case 2:
            game = new TrappistChess(play_one, play_two, first, dico, aff);
            break;
        case 3:
            game = new AntiChess(play_one, play_two, first, dico, aff);
            break;
        default:
            game = new ClassicChess(play_one, play_two, first, dico, aff);
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

/*
 * Test de python++
 */
bool SuperGame::click(std::string square){
    char* tmp = (char*)square.c_str();
    tmp[0] = std::toupper(tmp[0]);
    square = tmp;
    std::vector<std::pair<int,int> > possibleMov;
    std::string mov = this->_lastClick + ";" + square;
    bool answer = false;
    if (std::find(this->_ListMov.begin(), this->_ListMov.end(), square) != this->_ListMov.end()) {
        std::pair<bool, bool> res = this->_game->execute_step(mov, this->_player1, false);
        this->_lastClick = " ";
        this->_ListMov.clear();
        if (res.first) {
            this->_client->mov(mov);
            answer = res.second;
        } else {
            this->_bufferMov.push_back(mov);
        }
    } else {
        this->_lastClick = square;
        possibleMov = this->_game->return_pe_mov(square, this->_player1);
        this->_ListMov.clear();
        for(std::pair<int,int> elem : possibleMov){
            this->_ListMov.push_back(pairToString(elem));
        }
    }
    this->_client->movPossibleUpdate(&possibleMov);
    return answer;

    //std::vector<std::pair<int,int> > possibleMov;
    //std::string mov = this->_lastClick + ";" + square;
    //bool answer = false;
    //if (this->_lastClick == " "){
    //    this->_lastClick = square;
    //}else if (this->_game->myTurn(this->_player1)){
    //    std::pair<bool, bool> res = this->_game->execute_step(mov, this->_player1, false);
    //    answer = res.second;
    //    if (res.first){
    //        this->_lastClick = " ";
    //        this->_client->mov(mov);
    //    }else{
    //        possibleMov = this->_game->return_pe_mov(this->_lastClick);
    //        this->_lastClick = square;
    //        this->_ListMov.clear();
    //        for(std::pair<int,int> elem : possibleMov){
    //            this->_ListMov.push_back(pairToString(elem));
    //        }
    //    }
    //}else{
    //    this->_bufferMov.push_back(mov);
    //    this->_lastClick = " ";
    //}
    //this->_client->movPossibleUpdate(&possibleMov);
    //return answer;
}

int SuperGame::opponentMov(std::string mov){
    std::cout << "opponentMov: " << mov << ", " << this->_player2 << ", " << this->_inverted << std::endl;
    int result = 0;
    std::pair<bool, bool> res = this->_game->execute_step(mov, this->_player2, true);// this->_inverted);
    std::cout << "answer from game: " << res.first << std::endl;
    this->_ListMov.clear();
    //this->_client->movPossibleUpdate(this->_ListMov);
	if (res.second)
		result = -1;
	else if (! this->_bufferMov.empty()){
		mov = this->_bufferMov.front();
		this->_bufferMov.erase(_bufferMov.begin());
        res = this->_game->execute_step(mov, this->_player1, false);// this->_inverted);
		if (res.first) {
            this->_client->mov(mov);
            if(res.second) {
                //this->_client->movPossibleUpdate(this->_ListMov);
                result = 1;
            }
        } else{ 
            this->_bufferMov.clear();
        }
	}
    std::vector<std::pair<int,int> > possibleMov;
    this->_client->movPossibleUpdate(&possibleMov);
	return result;
}

std::pair<bool, bool> SuperGame::serverMov(std::string mov, std::string username, bool inverted){
    std::pair<bool, bool> res =  this->_game->execute_step(mov, username, inverted);
    return res;
}

std::string SuperGame::pairToString(std::pair<int, int> p){
    char ch = 'A' + p.first;
    std::string res =  ch + std::to_string(p.second+1);
    return res;
}

#endif
