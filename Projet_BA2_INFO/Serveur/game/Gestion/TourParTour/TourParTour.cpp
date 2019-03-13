
#include "TourParTour.hpp"

//--------------------TourParTour----------------------------------------------------------------------------------------------------

TourParTour::TourParTour(BaseChess* jeu) : TempsReel(jeu){} //*< Constructor

bool TourParTour::execute_step(){

	bool end = TempsReel::execute_step();
	
	if (end == false){this->change_active_player();}
	
	return end;
	
}
