#pragma once
#ifndef SILENCEDHUMAN_CPP
#define SILENCEDHUMAN_CPP
#include "SilencedHuman.hpp"

SilencedHuman::SilencedHuman(std::string nom,std::string lang) : Human(nom,lang) {} //*< Constructor
SilencedHuman::SilencedHuman() : Human("","") {} //*< Constructor

SilencedHuman::SilencedHuman(const SilencedHuman& SilencedHuman): Human(SilencedHuman) {}

std::string SilencedHuman::get_type_prefix() const{
	return "SilencedHuman";
}

void SilencedHuman::send_msg(std::string msg,bool endline){
	
	(void)msg;
	(void)endline;
		
}
#endif