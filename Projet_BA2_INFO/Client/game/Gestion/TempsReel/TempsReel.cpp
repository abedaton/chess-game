
#pragma once
#ifndef TEMPSREEL_CPP
#define TEMPSREEL_CPP

#include "TempsReel.hpp"

//--------------------TempsReel----------------------------------------------------------------------------------------------------

TempsReel::TempsReel(BaseChess* jeu) : game(jeu){} //*< Constructor

bool TempsReel::execute_step(){
	
	std::pair<bool,std::string> result = this->get_game()->execute_step();
	bool end = result.first;
	
	return end;
	
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
