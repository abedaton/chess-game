
#include "Human.hpp"

Human::Human(std::string nom,std::string lang) : Player(nom,lang) {} //*< Constructor
Human::Human() : Player("","") {} //*< Constructor

Human::Human(const Human& human): Player(human) {}

std::string Human::next_input(){
	
	std::string inp;
	
	std::cin>>inp;

	return inp;
	
}

std::string Human::get_type_prefix() const{
	return "Human";
}
