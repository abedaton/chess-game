#ifndef PENDULE_CPP
#define PENDULE_CPP

#include "Pendule.hpp"


//--------------------Pendule----------------------------------------------------------------------------------------------------

Pendule::Pendule(BaseChess* jeu) : BaseGameType(jeu), _timer(new Pendulum(10)) {_timer->run();} //*< Constructor

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
	int player;
	if(this->is_high_active()){
		player = 0;
	}else{
		player = 1;
	}
	_timer->pushChrono(player);
	std::pair<bool,bool> result = BaseGameType::execute_step(merged_coords,player_name,invert);
	_timer->stopChrono(player);
	std::cout << "temps restant : " << _timer->getChrono(player).getTimeLeft() << std::endl;

	bool valid = result.first;
	bool end = result.second;

	std::cout<< _timer->getGameState() << std::endl;
	if (_timer->getGameState() != PLAYING){
		end = true;
	}
	
	if (end == false){this->change_active_player();}
	
	return std::make_pair(valid,end);

}
#endif
