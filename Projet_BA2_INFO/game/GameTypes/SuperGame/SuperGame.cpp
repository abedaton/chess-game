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
            game = new DarkChess(play_one, play_two, first, nullptr, dico, aff);
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
bool SuperGame::click(std::string square)                                                               {
    std::vector<std::pair<int,int> > possibleMov                                                        ;
    std::string mov = this->_lastClick + ";" + square                                                   ;
    bool answer = false                                                                                 ;
    if (this->_lastClick == " ")                                                                        {
        this->_lastClick = square                                                                       ;}  
    else if (this->_game->myTurn(this->_player1))                                                       {
        std::cout << "mov: " << mov << std::endl                                                        ;
        std::pair<bool, bool> res = this->_game->execute_step(mov, this->_player1, false)               ;// this->_inverted)
        answer = res.second                                                                             ;
        if (res.first)                                                                                  {
            this->_lastClick = " "                                                                      ;
            this->_client->mov(mov)                                                                     ;}
        else                                                                                            {
            std::cout << "bad mov" << std::endl                                                         ;
            possibleMov = this->_game->return_pe_mov(this->_lastClick)                                  ;
            this->_lastClick = square                                                                   ;}}
    else                                                                                                {
        std::cout << "Coup enregistré: " << mov << std::endl                                            ;
        this->_bufferMov.push_back(mov)                                                                 ;
        this->_lastClick = " "                                                                          ;}
    this->_client->movPossibleUpdate(&possibleMov)                                                      ;
    return answer                                                                                       ;


    //bool res = false;
    //char* tmp = (char*)square.c_str();
    //tmp[0] = std::toupper(tmp[0]);
    //square = tmp;
	//if(std::find(this->_ListMov.begin(), this->_ListMov.end(), square) != this->_ListMov.end()) {
    //    std::cout << "mov: " << this->_lastClick + ';' + square << std::endl; //TO DELETE
	//	res = this->turn(this->_lastClick + ';' + square);
	//	this->_lastClick = " ";
	//	_ListMov.clear();
	//} else {
	//	this->_lastClick = square;
	//	this->_ListMov = *(this->_game->possible_mov(square) );
    //}
    //this->_client->movPossibleUpdate(this->_ListMov);
    //return res;
}

//bool SuperGame::turn(std::string mov){
//    std::pair<bool, bool> res = this->_game->execute_step(mov, this->_player1, this->_inverted);
//    if (res.first) {
//	    this->_client->mov(mov);
//	} else {
//		this->_bufferMov.push_back(mov);
//	}
//	return res.second;
//}

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

#endif
