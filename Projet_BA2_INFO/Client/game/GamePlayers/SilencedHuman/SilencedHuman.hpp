
#pragma once
#ifndef SILENCED_HUMAN_HPP
#define SILENCED_HUMAN_HPP
//#include <iostream>
//#include <string>
//#include <vector>

#include "Human/Human.cpp"

class SilencedHuman: public Human{
	public:
        SilencedHuman(std::string,std::string); //*< Constructor
        SilencedHuman(); //*< Constructor //noexcept = default
        virtual ~SilencedHuman() noexcept = default; //Destructor
        SilencedHuman(const SilencedHuman&);
        SilencedHuman& operator= (const SilencedHuman&) noexcept = default;
        
        using Human::send_msg;
        virtual void send_msg(std::string,bool) override;
        
	private:
		virtual std::string get_type_prefix() const override;
};
#endif
