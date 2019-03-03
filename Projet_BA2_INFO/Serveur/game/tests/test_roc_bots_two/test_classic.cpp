
#include <iostream>
#include <sstream>

#include "../../GameIntelligence/GameIntelligence.cpp"

MyOstream mout("logfile.txt");

int main(){
	/* fonction principale */
	
	// "anglais" , "francais" , "neerlandais"
	
	GameIntelligence* game = new GameIntelligence();
	
	game->make_classic_game_two_bots("bot_four","bot_three");
	game->execute_game();
	
	return 0;
}
