
#pragma once
#ifndef BASEGAMETYPE_CPP
#define BASEGAMETYPE_CPP

#include "BaseGameType.hpp"

//--------------------BaseGameType----------------------------------------------------------------------------------------------------

BaseGameType::BaseGameType(BaseChess* jeu) : game(jeu){} //*< Constructor

std::pair<bool,std::string> BaseGameType::execute_step(){
	return this->get_game()->execute_step();
	
}

bool BaseGameType::is_high_active() const{
	return this->get_game()->get_high_player() == this->get_game()->get_active_player();
}

std::pair<bool,bool> BaseGameType::execute_step(std::string merged_coords,std::string player_name){
	return this->execute_step(merged_coords,player_name,false);
	
}

std::pair<bool,bool> BaseGameType::execute_step(std::string merged_coords,std::string player_name, bool invert){
	if (! this->myTurn(player_name))
		return std::pair<bool,bool>(false, false);

	return this->get_game()->execute_forced_step(merged_coords,invert,player_name);
}

BaseChess* BaseGameType::get_game() const{
	return this->game;
}

void BaseGameType::set_game(BaseChess* jeu){
	this->game = jeu;
}

Plateau* BaseGameType::get_plateau() const{
	return this->get_game()->get_plateau();
}

void BaseGameType::change_active_player(){
	this->get_game()->change_active_player();
}

/*
std::pair<int, int> BaseGameType::str_mov_to_int(std::string square){
	char line = std::toupper(square[0]);
	std::string col = square.substr(1, square.size());
	int int_line = 0; // ---------------------------------------------------------- enleve warning
	int int_col = std::stoi(col);
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
    for (unsigned i = 0; i < alphabet.size(); ++i){
        if (alphabet[i] == line){
            int_line = i;
        }
    }

	return std::make_pair(int_line, int_col);
}*/


std::vector<std::pair<int,int>> BaseGameType::return_pe_mov(std::string coords, std::string username){return this->get_game()->return_pe_mov(coords, username);}


bool BaseGameType::myTurn(std::string username){
	return this->game->myTurn(username);
}

#endif
