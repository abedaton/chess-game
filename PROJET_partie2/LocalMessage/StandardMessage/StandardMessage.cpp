
#include "StandardMessage.hpp"

void StandardMessage::send_msg(Player* play,std::string msg,bool endline){
	
	std::string nom_play = play->get_name();
	(void)nom_play;
	
	std::cout<<msg;
	
	if (endline == true){std::cout<<std::endl;}
	
}

void StandardMessage::send_msg(Player* play,std::string msg){
	this->send_msg(play,msg,false);	
}

std::string StandardMessage::recieve_msg(Player* play){
	
	std::string msg = play->next_input();
	
	return msg;
	
}
