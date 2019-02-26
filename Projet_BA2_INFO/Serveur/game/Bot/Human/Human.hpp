
#pragma once
#ifndef HUMAN_HPP
#define HUMAN_HPP
//#include <iostream>
//#include <string>
//#include <vector>

#include "Player/Player.cpp"

class Human: public Player{
	public:
        Human(std::string,std::string); //*< Constructor
        Human(); //*< Constructor //noexcept = default
        virtual ~Human() noexcept = default; //Destructor
        Human(const Human&);
        Human& operator= (const Human&) noexcept = default;
        
        virtual std::string next_input() override;
        
	private:
		virtual std::string get_type_prefix() const override;
};
#endif
