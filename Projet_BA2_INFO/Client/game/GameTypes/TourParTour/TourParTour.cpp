#pragma once
#ifndef TOURPARTOUR_HPP
#define TOUTPARTOUR_HPP
#include "TourParTour.hpp"

//--------------------TourParTour----------------------------------------------------------------------------------------------------

TourParTour::TourParTour(BaseChess* jeu) : BaseGameType(jeu){} //*< Constructor

std::pair<bool,std::string> TourParTour::execute_step(){

	std::pair<bool,std::string> result = BaseGameType::execute_step();
	bool end = result.first;
	std::string coords = result.second;
	
	if (end == false){this->change_active_player();}
	
	return std::make_pair(end,coords); // précaution suite a probleme de transmition suite a recuperation de membre
	
}

std::pair<bool,bool> TourParTour::execute_step(std::string merged_coords,std::string player_name, bool invert){

	std::pair<bool,bool> result = BaseGameType::execute_step(merged_coords,player_name,invert);
	bool valid = result.first;
	bool end = result.second;
	
	if (end == false){this->change_active_player();}
	
	return std::make_pair(valid,end);

}
#endif