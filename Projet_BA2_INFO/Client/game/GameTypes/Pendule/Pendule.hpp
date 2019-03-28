
#pragma once
#ifndef PENDULE_HPP
#define PENDULE_HPP

#include "../BaseGameType/BaseGameType.cpp"
#include "Pendulum/Pendulum.cpp"

class Pendule: public BaseGameType {	
	public:
        Pendule(BaseChess*); //*< Constructor
        Pendule() noexcept = default; //*< Constructor
        ~Pendule() noexcept = default; //Destructor
        Pendule(const Pendule&) noexcept = default;
        Pendule& operator= (const Pendule&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(std::string,std::string,bool) override;
        
        using BaseGameType::execute_step;
        private: 
        Pendulum* _timer; 

};
#endif
