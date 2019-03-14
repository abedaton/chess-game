
#pragma once
#ifndef PENDULE_HPP
#define PENDULE_HPP

#include "../TempsReel/TempsReel.cpp"

class Pendule: public TempsReel {	
	public:
        Pendule(BaseChess*); //*< Constructor
        Pendule() noexcept = default; //*< Constructor
        ~Pendule() noexcept = default; //Destructor
        Pendule(const Pendule&) noexcept = default;
        Pendule& operator= (const Pendule&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(std::string,std::string,bool) override;

};
#endif
