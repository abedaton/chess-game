#include "pendule.hpp"
#include <iostream>











//100 milliseconds = 1 seconde


int main(int argc, char *argv[]){

	
	//Pendule pendule(5*60);
	Pendule pendule(10);
	std::string test;
	
	
	

	pendule.run();
	while(pendule.getGameState() == PLAYING)
	{
	    std::cout << "enter player's 1 input ";
	    pendule.pushChrono(0);
	    
	    std::cin >> test;
	    pendule.stopChrono(0);

	    //if gamestate==PLAYING
	    std::cout << "enter player's 2 input ";
	    pendule.pushChrono(1);
	    std::cin >> test;
	    pendule.stopChrono(1);
	}
}
