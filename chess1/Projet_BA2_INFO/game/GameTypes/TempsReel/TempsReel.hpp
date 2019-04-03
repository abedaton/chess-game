
#pragma once
#ifndef TEMPSREEL_HPP
#define TEMPSREEL_HPP

#include "../BaseGameType/BaseGameType.cpp"

class TempsReel: public BaseGameType {	
	public:
        TempsReel(BaseChess*); //*< Constructor
        TempsReel() noexcept = default; //*< Constructor
        virtual ~TempsReel() noexcept = default; //Destructor
        TempsReel(const TempsReel&) noexcept = default;
        TempsReel& operator= (const TempsReel&) noexcept = default;
        bool myTurn(std::string) override;

};
#endif
