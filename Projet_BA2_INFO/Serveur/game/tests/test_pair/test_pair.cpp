
#include <iostream>

#include "../../common/Quadrinome/Trinome/Paire/Paire.hpp"

int main(){
	
	Paire<int,bool>* paire = new Paire<int,bool>(10,0);
	
	std::cout<<paire<<std::endl;
	
	std::cout<<paire->get_first()<<std::endl;
	
}
