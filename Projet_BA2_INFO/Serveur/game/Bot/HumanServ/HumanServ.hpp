
#pragma once
#ifndef HUMAN_SERV_HPP
#define HUMAN_SERV_HPP
//#include <iostream>
//#include <string>
//#include <vector>

#include "Human/Human.cpp"

class HumanServ: public Human{
	public:
        HumanServ(std::string,std::string); //*< Constructor
        HumanServ(); //*< Constructor //noexcept = default
        virtual ~HumanServ() noexcept = default; //Destructor
        HumanServ(const HumanServ&);
        HumanServ& operator= (const HumanServ&) noexcept = default;
        
        using Human::send_msg;
        virtual void send_msg(std::string,bool) override;
        
	private:
		virtual std::string get_type_prefix() const override;
};
#endif
