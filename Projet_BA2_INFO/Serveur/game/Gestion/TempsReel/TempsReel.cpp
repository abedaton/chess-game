
#pragma once
#ifndef TEMPSREEL_CPP
#define TEMPSREEL_CPP

#include "TempsReel.hpp"

//--------------------TempsReel----------------------------------------------------------------------------------------------------

TempsReel::TempsReel(BaseChess* jeu) : game(jeu){} //*< Constructor

std::pair<bool,std::string> TempsReel::execute_step(){
	return this->get_game()->execute_step();
	
}

std::pair<bool,bool> TempsReel::execute_step(std::string merged_coords,std::string player_name){
	return this->get_game()->execute_forced_step(merged_coords,player_name);
	
}

BaseChess* TempsReel::get_game() const{
	return this->game;
}

void TempsReel::set_game(BaseChess* jeu){
	this->game = jeu;
}

void TempsReel::change_active_player(){
	this->get_game()->change_active_player();
}

#endif
