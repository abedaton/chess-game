
#include "Pendule.hpp"

//--------------------Pendule----------------------------------------------------------------------------------------------------

Pendule::Pendule(BaseChess* jeu) : TempsReel(jeu){} //*< Constructor

bool Pendule::execute_step(){ // temporairement identique a tour par tour !

	bool end = TempsReel::execute_step();
	
	if (end == false){this->change_active_player();}
	
	return end;
	
}
