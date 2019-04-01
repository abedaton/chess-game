#pragma once
#ifndef PENDULE_CPP
#define PENDULE_CPP

#include "Pendule.hpp"


//--------------------Pendule----------------------------------------------------------------------------------------------------


Pendule::Pendule(BaseChess* jeu, bool player) : BaseGameType(jeu), _timer(new Pendulum(10, static_cast<int>(player))) {_timer->run();_player = static_cast<int>(player);} //*< Constructor

std::pair<bool,std::string> Pendule::execute_step(){
	int player;
	if(this->is_high_active()){
		player = 0;
	}
	else{
		player = 1;
	}
	_timer->pushChrono(player);
	std::pair<bool,std::string> result = BaseGameType::execute_step();
	_timer->stopChrono(player);
	std::cout << "temps restant : " << _timer->getChrono(player).getTimeLeft() << std::endl;
	bool end = result.first;
	std::string coords = result.second;

	std::cout<< _timer->getGameState() << std::endl;
	if (_timer->getGameState() != PLAYING){
		end = true;
	}
	

	if (end == false){this->change_active_player();}
	
	return std::make_pair(end,coords); // précaution suite a probleme de transmition suite a recuperation de membre
	
}

std::pair<bool,bool> Pendule::execute_step(std::string merged_coords,std::string player_name, bool invert){
	_timer->pushChrono(_player);

	if (! this->myTurn(player_name)){
		_timer->stopChrono(_player);
		return std::pair<bool,bool>(false, false);
	}
	
	//std::cout << "joueur actuel : " << _player << std::endl;
	std::pair<bool,bool> result = BaseGameType::execute_step(merged_coords,player_name,invert);
	_timer->stopChrono(_player);
	std::cout << "temps restant : " << _timer->getChrono(_player).getTimeLeft() << std::endl; 

	bool valid = result.first;
	bool end = result.second;

	//std::cout<< _timer->getGameState() << std::endl;
	if (_timer->getGameState() != PLAYING){
		end = true;
	}
	
	if (end == false && valid == true){this->change_active_player();}
	
	return std::make_pair(valid,end);

}
#endif
