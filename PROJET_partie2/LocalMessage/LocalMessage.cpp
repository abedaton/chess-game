
#include "LocalMessage.hpp"

void LocalMessage::send_msg(Player* play,std::string msg,bool endline){
	
	std::string nom_play = play->get_name();
	(void)nom_play;
	
	mout<<msg;
	
	if (endline == true){mout<<std::endl;}
	
}

std::string LocalMessage::recieve_msg(Player* play){
	
	std::string msg = StandardMessage::recieve_msg(play);
	mout.log_only(msg,true);
	
	return msg;
	
}
