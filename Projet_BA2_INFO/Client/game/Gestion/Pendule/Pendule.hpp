
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
        
        bool execute_step() override;

};
#endif
