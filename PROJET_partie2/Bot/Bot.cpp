
#include "Bot.hpp"

Bot::Bot(std::string nom) : Player(nom), counter(0), move_list(std::vector<std::string>()) {} //*< Constructor

Bot::Bot(const Bot& bot): Player(bot), counter(bot.counter), move_list(bot.move_list) {}

std::string Bot::next_input(){
	
	std::string inp;
	
	std::vector<std::string> vect = this->move_list;
	
	if (counter < int(vect.size())){inp = vect[counter];}
	else{inp = "";}
	
	this->counter += 1;
	
	std::cout<<inp<<std::endl;
	
	return inp;
	
}

void Bot::set_moves(std::vector<std::string> vect){
	
	this->move_list = vect;
	
	}

std::string Bot::get_type_prefix() const{
	return "Bot";
}
