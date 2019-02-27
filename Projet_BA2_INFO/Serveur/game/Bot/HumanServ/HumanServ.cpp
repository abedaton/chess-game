
#include "HumanServ.hpp"

HumanServ::HumanServ(std::string nom,std::string lang) : Human(nom,lang) {} //*< Constructor
HumanServ::HumanServ() : Human("","") {} //*< Constructor

HumanServ::HumanServ(const HumanServ& HumanServ): Human(HumanServ) {}

std::string HumanServ::get_type_prefix() const{
	return "HumanServ";
}

void HumanServ::send_msg(std::string msg,bool endline){
	
	(void)msg;
	(void)endline;
		
}
