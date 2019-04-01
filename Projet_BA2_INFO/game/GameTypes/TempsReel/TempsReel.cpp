#pragma once
#ifndef TEMPSREEL_CPP
#define TEMPSREEL_CPP

#include "TempsReel.hpp"

//--------------------TempsReel----------------------------------------------------------------------------------------------------

TempsReel::TempsReel(BaseChess* jeu) : BaseGameType(jeu){} //*< Constructor

bool TempsReel::myTurn(std::string){
    return true;
}

// distinction TempsReel et BaseGameType pour plus de clarté

#endif